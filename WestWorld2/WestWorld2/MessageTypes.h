#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include<string>

enum message_type{
	Msg_HiHoneyImHome,
	Msg_StewReady,
};

inline std::string MsgToStr(int msg){
	switch(msg){
		case Msg_HiHoneyImHome:
			return "HiHoneyImHome";
		case Msg_StewReady:
			return "StrewReady";
		default:
			return "NotRecognized";
	}
}

#endif