#ifndef __XE_EVENTMOUSE_H__
#define __XE_EVENTMOUSE_H__

namespace xe {

class EventMouse {

public:
	enum class MouseEventType {
		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_MOVE,
		MOUSE_SCROLL
	};

	enum class MouseButton {
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_MIDDLE
	};

	EventMouse();
	~EventMouse();

private:

};

EventMouse::EventMouse() {}

EventMouse::~EventMouse() {}

}

#endif // !__XE_EVENTMOUSE_H__
