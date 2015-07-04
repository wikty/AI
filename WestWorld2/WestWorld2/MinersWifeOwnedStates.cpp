#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//----------------------WifesGlobalState's methods
WifesGlobalState* WifesGlobalState::Instance(){
	static WifesGlobalState instance;
	return &instance;
}

void WifesGlobalState::Execute(MinersWife* pWife){
	// 1 in 10 chance of needing the bathroom (provided she is not
	// already in the bathroom
	if((RandFloat() < 0.1) &&
		!pWife->GetFSM()->isInState(*VisitBathroom::Instance())){
			pWife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
}

bool WifesGlobalState::OnMessage(MinersWife* pWife, const Telegram& msg){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	switch(msg.Msg){
		case Msg_HiHoneyImHome:
			cout << "\nMessage handle by " << GetNameOfEntity(pWife->ID())
				<< " at time: " << Clock->GetCurrentTime();
			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pWife->ID())
				<< ": Hi honey. Let me make you some of mah fine country stew";
			pWife->GetFSM()->ChangeState(CookStew::Instance());
			return true;
	}
	return false;
}

//------------------------------DoHouseWork's methods
DoHouseWork* DoHouseWork::Instance(){
	static DoHouseWork instance;
	return &instance;
}

void DoHouseWork::Enter(MinersWife* pWife){
	cout << "\n" <<
		GetNameOfEntity(pWife->ID()) << " : Time to do some more housework!";
}

void DoHouseWork::Execute(MinersWife* pWife){
	switch(RandInt(0, 2)){
		case 0:
			cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Moppin' the floor";
			break;
		case 1:
			cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Makin' the bed";
			break;
		case 2:
			cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Washin' the dishes";
			break;
	}
}

void DoHouseWork::Exit(MinersWife* pWife){
}

bool DoHouseWork::OnMessage(MinersWife* pWife, const Telegram& msg){
	return false;
}

//--------------------------VisitBathroom's methods
VisitBathroom* VisitBathroom::Instance(){
	static VisitBathroom instance;
	return &instance;
}

void VisitBathroom::Enter(MinersWife* pWife){
	cout << "\n" << GetNameOfEntity(pWife->ID()) <<
		": Walkin' to the can. Need to powda mah pretty li'lle nose";
}

void VisitBathroom::Execute(MinersWife* pWife){
	cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Ahhhhhhh! Sweet relief!";
	pWife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* pWife){
	cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Leavin' the Jon";
}

bool VisitBathroom::OnMessage(MinersWife* pWife, const Telegram &msg){
	return false;
}

//--------------------------CookStew's methods
CookStew* CookStew::Instance(){
	static CookStew instance;
	return &instance;
}

void CookStew::Enter(MinersWife* pWife){
	if(!pWife->Cooking()){
		cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Putting the stew in the oven";
		
		// send a delayed message myself so that i know when to take the stew
		// out of oven
		Dispatch->DispatchMessage(1.5, // time delay
			pWife->ID(), // sender
			pWife->ID(), // receiver
			Msg_StewReady, // msg
			NO_ADDITIONAL_INFO);
		pWife->SetCooking(true);
	}
}

void CookStew::Execute(MinersWife* pWife){
	cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Fussin' over food";
}

void CookStew::Exit(MinersWife* pWife){
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pWife->ID()) << ": Puttin' the stew on the table";
}

bool CookStew::OnMessage(MinersWife* pWife, const Telegram& msg){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	switch(msg.Msg){
		case Msg_StewReady:
			cout << "\nMessage received by " << GetNameOfEntity(pWife->ID())
				<< " at time: " << Clock->GetCurrentTime();
			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pWife->ID()) << ": StewReady! Lets eat";

			// let hubby know the stew is ready
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
				pWife->ID(),
				ent_Miner_Bob,
				Msg_StewReady,
				NO_ADDITIONAL_INFO);
			pWife->SetCooking(false);
			pWife->GetFSM()->ChangeState(DoHouseWork::Instance());
			return true;
	}
	return false;
}

