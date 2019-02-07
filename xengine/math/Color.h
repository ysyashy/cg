#ifndef __XE_MATH_COLOR_H__
#define __XE_MATH_COLOR_H__

#include <cinttypes>

namespace xe {

struct Color {
	uint8_t R,
		G,
		B,
		A;

	Color() : R(0), G(0), B(0), A(0) {}
	Color(uint8_t InR, uint8_t InG, uint8_t InB, uint8_t InA = 255) : R(InR), G(InG), B(InG), A(InA) {}

	explicit Color(const Color &color) : R(color.R), G(color.G), B(color.B), A(color.A) {}

	const static Color white;
	const static Color black;
	const static Color gray;
	 
	const static Color red;
	const static Color orange;
	const static Color yellow;
	const static Color green;
	const static Color cyan;
	const static Color blue;
	const static Color purple;
};

}

#endif // !__XE_MATH_COLOR_H__

