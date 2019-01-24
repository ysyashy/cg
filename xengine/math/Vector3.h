#ifndef __XE_MATH_VECTOR_H__
#define __XE_MATH_VECTOR_H__

namespace xe {

struct Vector3 {
	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0){}
	Vector3(float px, float py, float pz) : X(px), Y(py), Z(pz) {}
	Vector3(const Vector3 &o) : X(o.X), Y(o.Y), Z(o.Z) {}
	
	Vector3 &operator=(const Vector3 &o) {
		this->X = o.X;
		this->Y = o.Y;
		this->Z = o.Z;
	}

	bool operator==(const Vector3 &o) {
		return this->X == o.X && this->Y == o.Y && this->Z == o.Z;
	}

};

}

#endif // !__XE_MATH_VECTOR_H__

