#include <cmath>
#include "XEMathUtility.h"
#include "Rect.h"
#include "Matrix.h"
#include "FQuat.h"
#include "Color.h"

namespace xe {

// Color.h
const Color Color::white(255, 255, 255, 255);
const Color Color::black(0, 0, 0, 1);
const Color Color::gray(128, 128, 128, 255);

const Color Color::red(255, 0, 0, 255);
const Color Color::orange(255, 125, 0, 255);
const Color Color::yellow(255, 255, 0, 255);
const Color Color::green(0, 255, 0, 255);
const Color Color::cyan(0, 255, 255, 255);
const Color Color::blue(0, 0, 255, 255);
const Color Color::purple(255, 0, 255, 255);

// FQuat.h
const FQuat FQuat::identify = {0, 0, 0, 1};

// Rect.h
const Rect Rect::zero(0.0f, 0.0f, 0.0f, 0.0f);

const Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);

// Matrix.h
const Matrix Matrix::identify(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);

const Matrix Matrix::zero(
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f);

FQuat FRotator::Quaternion() const {
	const float DEG_TO_RAD = PI / (180.f);
	const float DIVIDE_BY_2 = DEG_TO_RAD / 2.f;
	float SP, SY, SR;
	float CP, CY, CR;

	FMath::SinCos(&SP, &CP, Pitch*DIVIDE_BY_2);
	FMath::SinCos(&SY, &CY, Yaw*DIVIDE_BY_2);
	FMath::SinCos(&SR, &CR, Roll*DIVIDE_BY_2);

	FQuat RotationQuat;
	RotationQuat.X = CR * SP*SY - SR * CP*CY;
	RotationQuat.Y = -CR * SP*CY - SR * CP*SY;
	RotationQuat.Z = CR * CP*SY - SR * SP*CY;
	RotationQuat.W = CR * CP*CY + SR * SP*SY;

	return RotationQuat;
}

FQuat FQuat::MakeFromEuler(const Vector3 & euler) {
	return FRotator::MakeFromEuler(euler).Quaternion();
}

Vector3 FQuat::Euler() const {
	return Vector3(0, 0, 0);
}

FRotator FQuat::Rotator() const {
	const float SingularityTest = Z * X - W * Y;
	const float YawY = 2.f*(W*Z + X * Y);
	const float YawX = (1.f - 2.f*(FMath::Square(Y) + FMath::Square(Z)));

	// reference 
	// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/

	// this value was found from experience, the above websites recommend different values
	// but that isn't the case for us, so I went through different testing, and finally found the case 
	// where both of world lives happily. 
	const float SINGULARITY_THRESHOLD = 0.4999995f;
	const float RAD_TO_DEG = (180.f) / PI;
	FRotator RotatorFromQuat;

	if (SingularityTest < -SINGULARITY_THRESHOLD) {
		RotatorFromQuat.Pitch = -90.f;
		RotatorFromQuat.Yaw = FMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		RotatorFromQuat.Roll = FRotator::NormalizeAxis(-RotatorFromQuat.Yaw - (2.f * FMath::Atan2(X, W) * RAD_TO_DEG));
	} else if (SingularityTest > SINGULARITY_THRESHOLD) {
		RotatorFromQuat.Pitch = 90.f;
		RotatorFromQuat.Yaw = FMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		RotatorFromQuat.Roll = FRotator::NormalizeAxis(RotatorFromQuat.Yaw - (2.f * FMath::Atan2(X, W) * RAD_TO_DEG));
	} else {
		RotatorFromQuat.Pitch = FMath::FastAsin(2.f*(SingularityTest)) * RAD_TO_DEG;
		RotatorFromQuat.Yaw = FMath::Atan2(YawY, YawX) * RAD_TO_DEG;
		RotatorFromQuat.Roll = FMath::Atan2(-2.f*(W*X + Y * Z), (1.f - 2.f*(FMath::Square(X) + FMath::Square(Y)))) * RAD_TO_DEG;
	}
	return RotatorFromQuat;
}

FQuat::FQuat(const Vector3 & privot, const float angle) {
	const float halfTheta = angle / 2;
	const float sinHalfTheta = (float)sin(halfTheta);
	const float cosHalfTheta = (float)cos(halfTheta);

	X = sinHalfTheta * privot.X;
	Y = sinHalfTheta * privot.Y;
	Z = sinHalfTheta * privot.Z;
	W = cosHalfTheta;
}

float FRotator::NormalizeAxis(float Angle) {
	// returns Angle in the range[0, 360)
	Angle = ClampAxis(Angle);

	if (Angle > 180.f) {
		// shift to (-180,180]
		Angle -= 360.f;
	}

	return Angle;
}

inline float FRotator::ClampAxis(float Angle) {
	// returns Angle in the range (-360,360)
	Angle = FMath::Fmod(Angle, 360.f);

	if (Angle < 0.f) {
		// shift to [0,360) range
		Angle += 360.f;
	}

	return Angle;
}


FRotator FRotator::MakeFromEuler(const Vector3 & euler) {
	return FRotator(euler.X, euler.Y, euler.Z);
}

Vector3 FRotator::Euler() const {
	return Vector3(Roll, Pitch, Yaw);
}

Matrix Matrix::operator*(const Matrix & m) const {
	Matrix res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.m[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				res.m[i][j] += (*this).m[i][k] * m.m[k][j];
			}
		}
	}
	return res;
}

Matrix Matrix::translate(const Vector3 & v) const {
	Matrix ret = *this;
	ret.m[0][3] += v.X;
	ret.m[1][3] += v.Y;
	ret.m[2][3] += v.Z;
	return ret;
}

Matrix Matrix::rotation(const Vector3 & v) const {
	Matrix rotation = FQuat::MakeFromEuler(v).makeMatrix();
	return rotation * (*this);
}

Matrix Matrix::scale(const Vector3 & v) const {
	Matrix ret = *this;
	ret.m[0][0] *= v.X;
	ret.m[1][1] *= v.Y;
	ret.m[2][3] *= v.Z;
	return ret;
}


}