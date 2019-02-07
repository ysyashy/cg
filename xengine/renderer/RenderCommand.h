#pragma once

#include <GL/glew.h>
#include "math/XEMath.h"
#include "xeTypes.h"

namespace xe {

class GLProgram;
class Texture2D;

class RenderCommand {
public:
	enum class Type {
		Point,
		Line,
		Triangle
	};
public:
	void init(Type drawType, Texture2D *tex, GLProgram *program, BlendFunc blend, const VerticeList &vert, const Matrix &modelMat);
	void execute();
public:
	VerticeList _vert;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint textureID;

	BlendFunc blendFunc;

	GLProgram *glProgram;

	Matrix modelView;

	GLenum drawMode;
	int drawCount;
};

}
