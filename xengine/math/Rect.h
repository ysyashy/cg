#ifndef __XE_MATH_RECT_H__
#define __XE_MATH_RECT_H__

#include "Vector2.h"

namespace xe {

struct Rect {
	float X, Y;
	float W, H;

	explicit Rect(float InX, float InY, float InW, float InH) 
		: X(InX), Y(InY), W(InW), H(InH) {}

	explicit Rect(const Vector2 &start, const Vector2 &size)
		: X(start.X), Y(start.Y), W(size.X), H(size.Y) {}
	bool operator==(const Rect &o) const {
		return o.X == this->X && o.Y == this->Y
			&& o.W == this->W && o.H == this->H;
	}
public:
	const static Rect zero;
};

}

#endif // !__XE_MATH_RECT_H__

