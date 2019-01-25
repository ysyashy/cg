#ifndef __XE_TriangleCommand_H__
#define __XE_TriangleCommand_H__

#include <GL/glew.h>
#include "math/XEMath.h"
#include "xeTypes.h"
#include "IRenderCommand.h"

namespace xe {

class GLProgram;

class CommandTriangle : public IRenderCommand {
public:
	struct Triangles {
		Vert_Color_Tex *verts;
		unsigned short *indices;
		int vertCount;
		int indexCount;
	};
public:
	CommandTriangle();
	void init(GLuint textureId, GLProgram *glProgram, BlendFunc blendFunc, const Triangles &triangles, const Matrix &mv);
protected:
	GLuint _textureId;
	GLProgram *_glProgram;
	BlendFunc _blendFunc;
	Triangles _triangles;
	Matrix _modelView;
};

}

#endif