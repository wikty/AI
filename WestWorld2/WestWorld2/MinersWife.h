#ifndef MINERS_WIFE_H
#define MINERS_WIFE_H

#include <string>

#include "State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinersWifeOwnedStates.h"
#include "ConsoleUtils.h"
#include "Miner.h"
#include "StateMachine.h"
#include "Utils.h"

class MinersWife: public BaseGameEntity{
private:
	StateMachine<MinersWife>* m_pStateMachine;
	location_type m_Location;
	bool m_bCooking;
public:
	MinersWife(int id):m_Location(shack),
								m_bCooking(false),
								BaseGameEntity(id){
		m_pStateMachine = new StateMachine<MinersWife>(this);
		m_pStateMachine->SetCurrentState(DoHouseWork::Instance());
		m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
	}
	
	~MinersWife(){ delete m_pStateMachine; }

	void Update();

	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<MinersWife>* GetFSM()const{ return m_pStateMachine; }

	location_type Location()const{ return m_Location; }
	void ChangeLocation(const location_type location){ m_Location = location; }
	bool Cooking()const{ return m_bCooking; }
	void SetCooking(bool val){ m_bCooking = val; }

};

#endif

