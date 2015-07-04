#ifndef MINERS_WIFE_OWNED_STATES_H
#define MINERS_WIFE_OWNED_STATES_H

#include "State.h"

class MinersWife;

//----------------WifesGlobalState
class WifesGlobalState: public State<MinersWife>{
private:
	WifesGlobalState(){}
	WifesGlobalState(const WifesGlobalState&);
	WifesGlobalState& operator=(const WifesGlobalState&);
public:
	static WifesGlobalState* Instance();
	virtual void Enter(MinersWife* wife){}
	virtual void Execute(MinersWife* wife);
	virtual void Exit(MinersWife* wife){}
	virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};

//----------------DoHouseWork
class DoHouseWork: public State<MinersWife>{
private:
	DoHouseWork(){}
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);
public:
	static DoHouseWork* Instance();
	virtual void Enter(MinersWife* wife);
	virtual void Execute(MinersWife* wife);
	virtual void Exit(MinersWife* wife);
	virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};

//---------------VisitBathroom
class VisitBathroom: public State<MinersWife>{
private:
	VisitBathroom(){}
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);
public:
	static VisitBathroom* Instance();
	virtual void Enter(MinersWife* wife);
	virtual void Execute(MinersWife* wife);
	virtual void Exit(MinersWife* wife);
	virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};

//--------------------CookStew
class CookStew : public State<MinersWife>{
private:

  CookStew(){}
  CookStew(const CookStew&);
  CookStew& operator=(const CookStew&);
 
public:

  static CookStew* Instance();
  
  virtual void Enter(MinersWife* wife);

  virtual void Execute(MinersWife* wife);

  virtual void Exit(MinersWife* wife);

  virtual bool OnMessage(MinersWife* wife, const Telegram& msg);
};

#endif

