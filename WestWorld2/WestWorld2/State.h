#ifndef STATE_H
#define STATE_H

struct Telegram;

template<class entity_type>
class State{
	public:
		virtual ~State(){}

		// this is executed when state is entered
		virtual void Enter(entity_type *)=0;
		
		// this is  the state's normal update function
		virtual void Execute(entity_type*)=0;

		// this is executed when the state is exited
		virtual void Exit(entity_type*)=0;
		
		// this executes if the agent receives a message from the
		// message dispatcher
		virtual bool OnMessage(entity_type*, const Telegram&)=0;
};
#endif