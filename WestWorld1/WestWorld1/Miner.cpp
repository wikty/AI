#include "Miner.h"
#include "MinerOwnedStates.h"

Miner::Miner(int id):BaseGameEntity(id),
								m_Location(shack),
								m_iGoldCarried(0),
								m_iMoneyInBank(0),
								m_iThirst(0),
								m_iFatigue(0),
								m_pCurrentState(GoHomeAndSleepTilRested::Instance()){
}

void Miner::ChangeState(State* pNewState){
	assert(m_pCurrentState && pNewState);
	m_pCurrentState->Exit(this);
	m_pCurrentState = pNewState;
	m_pCurrentState->Enter(this);
}

void Miner::AddToGoldCarried(const int val){
	m_iGoldCarried += val;
	if(m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Miner::AddToWealth(const int val){
	m_iMoneyInBank += val;
	if(m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Miner::Thirsty()const{
	if(m_iThirst >= ThirstLevel){
		return true;
	}
	return false;
}

void Miner::Update(){
	m_iThirst += 1;
	if(m_pCurrentState){
		m_pCurrentState->Execute(this);
	}
}

bool Miner::Fatigued()const{
	if(m_iFatigue > TirednessThreshold){
		return true;
	}
	return false;
}

