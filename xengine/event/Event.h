#ifndef __XE_EVENT_H__
#define __XE_EVENT_H__

namespace xe {

class Event {
public:
	enum class Type {
		KEYBOARD,
		MOUSE
	};
protected:
	Event(){}
	~Event(){}
	Type _type;
};

}

#endif // !__XE_EVENT_H__
