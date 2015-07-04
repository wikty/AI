#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

//#pragma warning(disable: 4786)
#include<set>
#include"ConsoleUtils.h"
#include"Telegram.h"

class BaseGameEntity;

// to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0f;
const int NO_ADDITIONAL_INFO = 0;

// make using easier
#define Dispatch MessageDispatcher::Instance()



class MessageDispatcher{
private:
	// std::set is used as the container for the delayed messages
	// because of the benefit of automatic sorting and avoidance
	// of duplicats, messages are sorted by their dispatch time.
	std::set<Telegram> PriorityQ;
	
	// this method is utilized by DispatchMessage or DispatchDelayedMessages
	// this method calls the message handling memeber function of the receiving
	// entity, pReceiver, with the newly created telegram
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	// this is a singleton
	MessageDispatcher(){}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
public:
	static MessageDispatcher* Instance();
	
	// send a message to another agent, receiving agent is referenced by ID
	void DispatchMessage(double delay,
										int sender,
										int receiver,
										int msg,
										void* info);
	
	// send out any delayed messages, this method is called each time through
	// the main game loop
	void DispatchDelayedMessages();
};

#endif

	
