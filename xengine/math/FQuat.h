#ifndef __XE_FQUAT_H__
#define __XE_FQUAT_H__

#include "Vector3.h"
#include <cmath>

namespace xe {

struct FRotator;

struct FQuat {

	float X, Y, Z, W;
	FQuat(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f, float InW = 1.0f)
		: X(InX), Y(InY), Z(InZ), W(InW) {}
	FQuat(const FQuat &o)
		: X(o.X), Y(o.Y), Z(o.Z), W(o.W) {}

	FQuat(const Vector3 &privot, float angle);

	void operator=(const FQuat &o) {
		this->X = o.X;
		this->Y = o.Y;
		this->Z = o.Z;
		this->W = o.W;
	}

	bool operator==(const FQuat &o) {
		return this->X == o.X && this->Y == o.Y
			&& this->Z == o.Z && this->W == o.W;
	}

public:
	FRotator Rotator() const;
	static FQuat MakeFromEuler(const Vector3 &euler);
	Vector3 Euler() const;
};

FQuat::FQuat(const Vector3 & privot, const float angle) {
	const float halfTheta = angle / 2;
	const float sinHalfTheta = (float)sin(halfTheta);
	const float cosHalfTheta = (float)cos(halfTheta);

	X = sinHalfTheta * privot.X;
	Y = sinHalfTheta * privot.Y;
	Z = sinHalfTheta * privot.Z;
	W = cosHalfTheta;
}

}

#endif // !__XE_FQUAT_H__
