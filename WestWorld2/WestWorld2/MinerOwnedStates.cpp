#include "MinerOwnedStates.h"
#include "State.h"
#include "Miner.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "CrudeTimer.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include "Telegram.h"

#include <iostream>
using std::cout;

// define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//----------EnterMineAndDigForNugget's methods
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance(){
	static EnterMineAndDigForNugget instance;
	return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner){
	// if miner is not already located at the goldmine, he
	// must change location to the gold mine
	if(pMiner->Location() != goldmine){
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout <<"\n" << GetNameOfEntity(pMiner->ID()) << ":" << "Walkin' to the goldmine";
		
		pMiner->ChangeLocation(goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* pMiner){
	// miner digs for gold until he is carrying in excess of MaxNuggets
	// if he gets thirsty during his digging he packs up work for a while
	// and change state to go to the saloon for a whiskey
	pMiner->AddToGoldCarried(1);
	pMiner->IncreaseFatigue();

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":" << "Pickin' up a nugget";
	
	if(pMiner->PocketsFull()){
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}
	if(pMiner->Thirsty()){
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
		<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}

bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg){
	// send msg to global message handler
	return false;
}

//------------------VisitBandAndDepositGold's methods
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance(){
	static VisitBankAndDepositGold instance;
	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner){
	if(pMiner->Location() != bank){
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
			<< "Goin' to the bank. Yes siree";
		
		pMiner->ChangeLocation(bank);
	}
}

void VisitBankAndDepositGold::Execute(Miner* pMiner){
	pMiner->AddToWealth(pMiner->GoldCarried());
	pMiner->SetGoldCarried(0);

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
		<< "Depositing gold. Total savings now: " << pMiner->Wealth();

	if(pMiner->Wealth() >= ComfortLevel){
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
			<< "WooHoo! Rich enough for now. Back home to mah li'lle lady";

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	else{
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
}

bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg){
	// send message to the global handler
	return false;
}

//--------------------------GoHomeAndSleepTilRested's methods
GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance(){
	static GoHomeAndSleepTilRested instance;
	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner){
	if(pMiner->Location() != shack){
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
			<< "Walkin' home";

		pMiner->ChangeLocation(shack);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, // time delay
			pMiner->ID(), // sender's ID
			ent_Elsa, // receiver's ID
			Msg_HiHoneyImHome, // the message
			NO_ADDITIONAL_INFO);
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner){
	if(!pMiner->Fatigued()){
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "What a God darn fantastic nap! Time to find more gold";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		pMiner->DecreaseFatigue();
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "ZZZ...";
	}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
		<< "Leaving the house";
}

bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	switch(msg.Msg){
		case Msg_StewReady:
			 cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) 
			 << " at time: " << Clock->GetCurrentTime();

			 SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

			 cout << "\n" << GetNameOfEntity(pMiner->ID()) 
				  << ": Okay Hun, ahm a comin'!";

			 pMiner->GetFSM()->ChangeState(EatStew::Instance());
		      
			 return true;
	}// end switch
	return false;
}

//----------------------QuenchThirst's methods
QuenchThirst* QuenchThirst::Instance(){
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner){
	if(pMiner->Location() != saloon){
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Boy, ah sure is thusty! Walking to the saloon for a whiskey";
		pMiner->ChangeLocation(saloon);
	}
}

void QuenchThirst::Execute(Miner* pMiner){
	if(pMiner->Thirsty()){
		pMiner->BuyAndDrinkAWhiskey();
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
			<< "That's mighty fine sippin liquer";
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "\nError!\nError";
	}
}

void QuenchThirst::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
		<< "Leaving the saloon, feelin' good";
}

bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg){
	// send to the global handler
	return false;
}

//------------------------------EatStew's methods
EatStew* EatStew::Instance(){
	static EatStew instance;
	return &instance;
}

void EatStew::Enter(Miner* pMiner){
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Miner* pMiner){
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Tastes real good too!";
	pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner){ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
	  << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}

bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg){
  //send msg to global message handler
  return false;
}
	
