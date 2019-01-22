#ifndef __XE_MATH_VECTOR2_H__
#define __XE_MATH_VECTOR2_H__

namespace xe {

struct Vector2 {
	float X;
	float Y;

	Vector2() : X(0), Y(0) {}
	Vector2(float px, float py) : X(px), Y(py) {}
	Vector2(const Vector2 &o) : X(o.X), Y(o.Y) {}

	Vector2 &operator=(const Vector2 &o) {
		this->X = o.X;
		this->Y = o.Y;
		return *this;
	}

	bool operator==(const Vector2 &o) {
		return o.X == this->X
			&& o.Y == this->Y;
	}
private:
	bool operator<(const Vector2 &o) { return false; }
	bool operator>(const Vector2 &o) { return false; }
};

}

#endif