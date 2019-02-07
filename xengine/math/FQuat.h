#pragma once

#include "Vector3.h"
#include "Matrix.h"
#include "FRotator.h"
#include <cmath>

namespace xe {

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

	Matrix makeMatrix(const Vector3& Origin = Vector3::zero) const {
		const float x2 = X + X;    const float y2 = Y + Y;    const float z2 = Z + Z;
		const float xx = X * x2;   const float xy = X * y2;   const float xz = X * z2;
		const float yy = Y * y2;   const float yz = Y * z2;   const float zz = Z * z2;
		const float wx = W * x2;   const float wy = W * y2;   const float wz = W * z2;
		Matrix mat;
		mat.m[0][0] = 1.0f - (yy + zz);	mat.m[1][0] = xy - wz;				mat.m[2][0] = xz + wy;			mat.m[3][0] = Origin.X;
		mat.m[0][1] = xy + wz;			mat.m[1][1] = 1.0f - (xx + zz);		mat.m[2][1] = yz - wx;			mat.m[3][1] = Origin.Y;
		mat.m[0][2] = xz - wy;			mat.m[1][2] = yz + wx;				mat.m[2][2] = 1.0f - (xx + yy);	mat.m[3][2] = Origin.Z;
		mat.m[0][3] = 0.0f;				mat.m[1][3] = 0.0f;					mat.m[2][3] = 0.0f;				mat.m[3][3] = 1.0f;
		return mat;
	}

	const static FQuat identify;

public:
	FRotator Rotator() const;
	static FQuat MakeFromEuler(const Vector3 &euler);
	Vector3 Euler() const;
};

}
