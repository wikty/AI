#ifndef MINER_H
#define MINER_H

#include <string>
#include <cassert>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "StateMachine.h"
#include "MinerOwnedStates.h"
#include "ConsoleUtils.h"


template<class entity_type> class State;
struct Telegram;

// the amount of glod a miner must have before he feels comfortable
const int ComfortLevel = 5;
// the amount of nuggets a miner can carry
const int MaxNuggets = 3;
// above this value a miner is thirsty
const int ThirstLevel = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;

class Miner: public BaseGameEntity{
	private:
		StateMachine<Miner>* m_pStateMachine;
		location_type m_Location;
		int m_iGoldCarried;
		int m_iMoneyInBank;
		int m_iThirst;
		int m_iFatigue;

	public:
		Miner(int id): m_Location(shack),
							m_iGoldCarried(0),
							m_iMoneyInBank(0),
							m_iThirst(0),
							m_iFatigue(0),
							BaseGameEntity(id){
			m_pStateMachine  = new StateMachine<Miner>(this);
			m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
		}

		~Miner(){ delete m_pStateMachine; }

		void Update();

		virtual bool HandleMessage(const Telegram& msg);

		StateMachine<Miner>* GetFSM()const{ return m_pStateMachine; }

		location_type Location()const{ return m_Location; }
		void ChangeLocation(const location_type location){ m_Location = location; }

		int GoldCarried()const{ return m_iGoldCarried; }
		void SetGoldCarried(const int val){ m_iGoldCarried = val; }
		void AddToGoldCarried(const int val);
		bool PocketsFull()const{ return m_iGoldCarried >= MaxNuggets; }

		bool Fatigued()const;
		void DecreaseFatigue(){ m_iFatigue -= 1; }
		void IncreaseFatigue(){ m_iFatigue += 1; }

		int Wealth()const{ return m_iMoneyInBank; }
		void SetWealth(const int val){ m_iMoneyInBank = val; }
		void AddToWealth(const int val);

		bool Thirsty()const;
		void BuyAndDrinkAWhiskey(){ m_iThirst = 0; m_iMoneyInBank -= 2; }

};

#endif







