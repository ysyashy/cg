#ifndef __XE_MATH_COLOR_H__
#define __XE_MATH_COLOR_H__

namespace xe {

struct Color {
	float R,
		G,
		B,
		A;

	Color() : R(0), G(0), B(0), A(0) {}
	Color(float InR, float InG, float InB, float InA = 1.0f) : R(InR), G(InG), B(InG), A(InA) {}

	explicit Color(const Color &color) : R(color.R), G(color.G), B(color.B), A(color.A) {}
};

}

#endif // !__XE_MATH_COLOR_H__

