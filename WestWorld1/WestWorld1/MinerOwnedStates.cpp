#include "MinerOwnedStates.h"
#include "State.h"
#include "Miner.h"
#include "Locations.h"
#include "../../common/misc/ConsoleUtils.h"
#include "EntityNames.h"

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
		pMiner->ChangeState(VisitBankAndDepositGold::Instance());
	}
	if(pMiner->Thirsty()){
		pMiner->ChangeState(QuenchThirst::Instance());
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ":"
		<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
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

		pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	else{
		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner){
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
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
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner){
	if(!pMiner->Fatigued()){
		SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "What a God darn fantastic nap! Time to find more gold";

		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
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
		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
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