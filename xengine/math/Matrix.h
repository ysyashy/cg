#ifndef __XE_MATH_MATRIX__
#define __XE_MATH_MATRIX__

#include "Vector4.h"

namespace xe {

struct Matrix {
	float m[4][4];

	Matrix(){}
	Matrix(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44) {
		m[0][0] = m11; m[0][1] = m12;  m[0][2] = m13;  m[0][3] = m14;
		m[1][0] = m21; m[1][1] = m22;  m[1][2] = m23;  m[1][3] = m24;
		m[2][0] = m31; m[2][1] = m32;  m[2][2] = m33;  m[2][3] = m34;
		m[3][0] = m41; m[3][1] = m42;  m[3][2] = m43;  m[3][3] = m44;
	}
	Matrix(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4) {
		m[0][0] = v1.X; m[0][1] = v1.Y;  m[0][2] = v1.Z;  m[0][3] = v1.Z;
		m[1][0] = v2.X; m[1][1] = v2.Y;  m[1][2] = v2.Z;  m[1][3] = v2.Z;
		m[2][0] = v3.X; m[2][1] = v3.Y;  m[2][2] = v3.Z;  m[2][3] = v3.Z;
		m[3][0] = v4.X; m[3][1] = v4.Y;  m[3][2] = v4.Z;  m[3][3] = v4.Z;
	}

	const static Matrix identify;
	const static Matrix zero;
};

}

#endif // !__XE_MATH_MATRIX__

