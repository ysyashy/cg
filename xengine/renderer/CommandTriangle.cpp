#include "CommandTriangle.h"

namespace xe {

CommandTriangle::CommandTriangle() {
	commandType = IRenderCommand::Type::TRIANGLES_COMMAND;
}

void CommandTriangle::init(GLuint textureId, GLProgram * glProgram, BlendFunc blendFunc, const Triangles & triangles, const Matrix & mv) {
	IRenderCommand::init(mv);
	_triangles = triangles;
	_modelView = mv;
	if (textureId != _textureId || _blendFunc.src != blendFunc.src || _blendFunc.dst != blendFunc.dst
		|| _glProgram != glProgram) {
		_textureId = textureId;
		_blendFunc = blendFunc;
		_glProgram = glProgram;
	}
}


}