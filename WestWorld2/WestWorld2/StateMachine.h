#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include"State.h"
#include"Telegram.h"

template<class entity_type>
class StateMachine{
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;
public:
	StateMachine(entity_type* owner): m_pOwner(owner),
														m_pCurrentState(NULL),
														m_pPreviousState(NULL),
														m_pGlobalState(NULL){
	}
	
	virtual ~StateMachine(){}

	void SetCurrentState(State<entity_type>* s){ m_pCurrentState = s; }
	void SetPreviousState(State<entity_type>* s){ m_pPreviousState = s; }
	void SetGlobalState(State<entity_type>* s){ m_pGlobalState = s; }

	void Update()const{
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	bool HandleMessage(const Telegram& msg)const{
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg)){
			return true;
		}
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg)){
			return true;
		}
		return false;
	}

	void ChangeState(State<entity_type>* pNewState){
		assert(pNewState && "<StateMachine::ChangeState>:trying to assgin null state to current");
		m_pPreviousState = m_pCurrentState;
		m_pPreviousState->Exit(m_pOwner);
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}

	void RevertToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	bool isInState(const State<entity_type>& state)const{
		if(typeid(*m_pCurrentState) == typeid(state)) return true;
		return false;
	}

	State<entity_type>* CurrentState()const{ return m_pCurrentState; }
	State<entity_type>* PreviousState()const{ return m_pPreviousState; }
	State<entity_type>* GlobalState()const{ return m_pGlobalState; }

	// only ever used during debugging to grab the name of the current state
	std::string GetNameOfCurrentState()const{
		std::string s(typeid(*m_pCurrentState).name());
		// remove the 'class' part from the front of the string
		if(s.size() >5){
			s.erase(0, 6);
		}
		return s;
	}
};

#endif