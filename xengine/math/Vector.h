#ifndef __XE_MATH_VECTOR_H__
#define __XE_MATH_VECTOR_H__

namespace xe {

struct Vector {
	float X;
	float Y;
	float Z;

	Vector() : X(0), Y(0), Z(0){}
	Vector(float px, float py, float pz) : X(px), Y(py), Z(pz) {}
	explicit Vector(const Vector &o) : X(o.X), Y(o.Y), Z(o.Z) {}
	
	Vector &operator=(const Vector &o) {
		this->X = o.X;
		this->Y = o.Y;
		this->Z = o.Z;
	}

	bool operator==(const Vector &o) {
		return this->X == o.X && this->Y == o.Y && this->Z == o.Z;
	}

};

}

#endif // !__XE_MATH_VECTOR_H__

