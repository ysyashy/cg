#ifndef __XE_MATH_VECTOR4__
#define __XE_MATH_VECTOR4__

#include "Vector.h"

namespace xe {

struct Vector4 {

	float X;
	float Y;
	float Z;
	float W;

	explicit Vector4(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f, float InW = 0.0f)
		:X(InX), Y(InY), Z(InZ), W(InW) {}
	Vector4(const Vector &InVec, float InW = 1.0f)
		: X(InVec.X), Y(InVec.Y), Z(InVec.Z), W(InW) {}
};

}

#endif // !__XE_MATH_VECTOR4__
