#pragma once

#include "Vector3.h"

namespace xe {

struct FQuat;

struct FRotator {
	/** Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down). **/
	float Pitch;
	/** Rotation around the up axis (around Z axis), Running in circles (0=East, +North, -South). **/
	float Yaw;
	/** Rotation around the forward axis (around X axis), Tilting your head, 0=Straight, +Clockwirse, -CCW. **/
	float Roll;

	static FRotator zeroRotator;
	FRotator(float InPitch = 0.0f, float InYaw = 0.0f, float InRoll = 0.0f)
		: Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

	FQuat Quaternion() const;

	static FRotator MakeFromEuler(const Vector3 &euler);
	Vector3 Euler() const;

	static float NormalizeAxis(float Angle);
	static float ClampAxis(float Angle);
};

}


