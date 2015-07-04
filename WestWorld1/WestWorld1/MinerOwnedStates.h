#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H

#include "State.h"

class Miner;

//--------------------EnterMineAndDigForNugget-----------------------
// In this state the miner will walk to a goldmine and pick up a nugget
// of gold, if the miner already has a nugget of gold he'll change state
// to VisitBankAndDepositGold, if he gets thirsty he'll change state to
// QuenchThirst
//-------------------------------------------------------------------------
class EnterMineAndDigForNugget: public State{
private:
	// this is a singleton
	EnterMineAndDigForNugget(){}
	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
	EnterMineAndDigForNugget& operator =(const EnterMineAndDigForNugget&);
public:
	static EnterMineAndDigForNugget* Instance();
	virtual void Enter(Miner* miner);
	virtual void Execute(Miner * miner);
	virtual void Exit(Miner* miner);

};

//-----------------------VisitBandAndDepositGold----------------------
// In this state miner will go to a bank and deposit any nuggets he is
// carrying, if the miner is subsequently wealthy enough he'll walk home
// otherwise he'll keep going to get more gold
class VisitBankAndDepositGold: public State{
private:
	// this is a singleton
	VisitBankAndDepositGold(){};
	VisitBankAndDepositGold(const VisitBankAndDepositGold&);
	VisitBankAndDepositGold& operator =(const VisitBankAndDepositGold&);
public:
	static VisitBankAndDepositGold* Instance();
	virtual void Enter(Miner* miner);
	virtual void Execute(Miner* miner);
	virtual void Exit(Miner* miner);

};

//----------------------GoHomeAndSleepTilRested----------------------
// In this state miner go home and sleep until his fatigue is decreased sufficiently
//----------------------------------------------------------------------------
class GoHomeAndSleepTilRested: public State{
private:
	// this is a singleton
	GoHomeAndSleepTilRested(){};
	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
	GoHomeAndSleepTilRested& operator =(const GoHomeAndSleepTilRested&);
public:
	static GoHomeAndSleepTilRested* Instance();
	virtual void Enter(Miner* miner);
	virtual void Execute(Miner* miner);
	virtual void Exit(Miner *miner);

};

//--------------------------QuenchThirst----------------------------
// In this state miner go to bar and drink a cup of whiskey
//-------------------------------------------------------------------
class QuenchThirst: public State{
private:
	// this is a singleton
	QuenchThirst(){};
	QuenchThirst(const QuenchThirst&);
	QuenchThirst& operator =(const QuenchThirst&);
public:
	static QuenchThirst* Instance();
	virtual void Enter(Miner* miner);
	virtual void Execute(Miner* miner);
	virtual void Exit(Miner* miner);

};

#endif
