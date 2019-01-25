#pragma once

#include "math/XEMath.h"
#include <GL/glew.h>

namespace xe {

struct Vert_Color_Tex {
	Vector3 vertice;
	Color color;
	Vector2 texCoord;
};

struct BlendFunc {
	/** source blend function **/
	GLenum src;
	/** dentination blend function **/
	GLenum dst;

	/** Blending disabled. Uses {GL_ONE, GL_ZERO} **/
	static const BlendFunc DISABLE;
	/** Blending enable for textures with Alpha premultiplied. Uses {GL_ONE, GL_ONE_MINUS_SRC_ALPHA} **/
	static const BlendFunc ALPHA_PREMULTIPLIED;
	/** Blending enabled for textures with Alpha NON premultiplied, Uses {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA} **/
	static const BlendFunc ALPHA_NON_PREMULTIPLIED;
	/** Enables Addition blending. Uses {GL_SRC_ALPHA, GL_ONE} **/
	static const BlendFunc ADDITIVE;

	bool operator==(const BlendFunc &o) const {
		return src == o.src && dst == o.dst;
	}
	bool operator!=(const BlendFunc &o) const {
		return src != o.src || dst != o.dst;
	}
	bool operator<(const BlendFunc &o) const {
		return src < o.src || (src == o.src && dst < o.dst);
	}
};

}
