#include"MessageDispatcher.h"
#include"CrudeTimer.h"
#include"BaseGameEntity.h"
#include"EntityManager.h"
#include"Locations.h"
#include"MessageTypes.h"
#include"EntityNames.h"

#include<iostream>
using std::cout;
using std::set;

#ifdef TEXTOUTPUT
#include<fstream>
extern std::ofstream os;
#define cout os
#endif

MessageDispatcher* MessageDispatcher::Instance(){
	static MessageDispatcher instance;
	return &instance;
}

void MessageDispatcher::Discharge(BaseGameEntity* pReceiver, const Telegram& msg){
	if(!pReceiver->HandleMessage(msg)){
		// telegram could not be handle
		cout << "Message not handled";
	}
}

void MessageDispatcher::DispatchMessage(double delay,
										int sender,
										int receiver,
										int msg,
										void* info){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	BaseGameEntity* pSender = EntityMgr->GetEntityByID(sender);
	BaseGameEntity* pReceiver = EntityMgr->GetEntityByID(receiver);

	if(pReceiver == NULL){
		cout << "\nWarning! No Receiver with ID of" << receiver << " found";
		return;
	}
	
	Telegram telegram(0, sender, receiver, msg, info);

	if(delay <= 0.0f){
		cout << "\nInstant telegram dispatched at time: " << Clock->GetCurrentTime()
			<< " by " << GetNameOfEntity(pSender->ID()) << " for "
			<< GetNameOfEntity(pReceiver->ID()) << ". Message is: " << MsgToStr(msg);
		Discharge(pReceiver, telegram);
	}
	else{
		double CurrentTime = Clock->GetCurrentTime();
		telegram.DispatchTime = CurrentTime + delay;
		PriorityQ.insert(telegram);
		cout << "\nDelayed telegram from " << GetNameOfEntity(pSender->ID())
			<< " recorded at time " << Clock->GetCurrentTime() << " for "
			<< GetNameOfEntity(pReceiver->ID()) << ". Message is: " << MsgToStr(msg);
	}
}

// this function dispatches any telegrams with a timestamp that has
// expired, any dispatched telegrams are removed from the priority queue
void MessageDispatcher::DispatchDelayedMessages(){
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	double CurrentTime = Clock->GetCurrentTime();
	while(!PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(PriorityQ.begin()->DispatchTime > 0)){
			const Telegram& telegram = *PriorityQ.begin();
			BaseGameEntity* pReceiver = EntityMgr->GetEntityByID(telegram.Receiver);
			cout << "\nQueued telegram read for dispatch: Sent to "
				<< GetNameOfEntity(pReceiver->ID()) << ". Message is: "
				<< MsgToStr(telegram.Msg);
			Discharge(pReceiver, telegram);
			PriorityQ.erase(PriorityQ.begin());
	}
}











