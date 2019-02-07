#include <cassert>
#include <algorithm>
#include <GL/glew.h>
#include "Sprite.h"
#include "renderer/Renderer.h"
#include "renderer/RenderCommand.h"
#include "renderer/GLProgram.h"
#include "Director.h"

namespace xe {

Sprite::Sprite(Texture2D *texture) 
	: _texture(texture) {
	_command = new RenderCommand();
	_program = new GLProgram(GLProgram::defaultVert, GLProgram::defaultFrag);
	_modelMat = Matrix::identify;
	init();
}
Sprite::~Sprite() {
	delete _command;
	delete _program;
}

void Sprite::init() {
	const Vector2 winSize = Director::getInstance()->getWinSize();
	const Vector2 s = getSize();
	const float factor = std::min(s.X / winSize.X, s.Y / winSize.Y);
	const float normalX = s.X * factor / winSize.X;
	const float normalY = s.Y * factor / winSize.Y;
	// quad: five vertices
	vert.vertCount = 4;
	vert.vertices = new Vert_Color_Tex[4];

	vert.vertices[0].vertice = { normalX, normalY, 0};
	vert.vertices[1].vertice = { normalX, -normalY, 0 };
	vert.vertices[2].vertice = { -normalX, -normalY, 0 };
	vert.vertices[3].vertice = { -normalX, normalY, 0 };

	vert.vertices[0].color = Color::white;
	vert.vertices[1].color = Color::white;
	vert.vertices[2].color = Color::white;
	vert.vertices[3].color = Color::white;

	vert.vertices[0].texCoord = { 1, 1 };
	vert.vertices[1].texCoord = { 1, 0 };
	vert.vertices[2].texCoord = { 0, 0 };
	vert.vertices[3].texCoord = { 0, 1 };

	vert.indexCount = 6;
	vert.indices = new unsigned short[6];
	vert.indices[0] = 0;
	vert.indices[1] = 1;
	vert.indices[2] = 3;
	vert.indices[3] = 1;
	vert.indices[4] = 2;
	vert.indices[5] = 3;

	_command->init(RenderCommand::Type::Triangle, _texture, _program, BlendFunc::ALPHA_PREMULTIPLIED, vert, _modelMat);
}

inline Vector2 Sprite::getSize() const {
	return Vector2((float)_texture->getWidth(), (float)_texture->getHeight());
}

void Sprite::draw(Renderer * renderer, const Matrix & mat) {
	_modelMat = Matrix::identify;
	_modelMat = _modelMat.rotation(rotation.Euler());
	_modelMat = _modelMat.scale(scale);
	_modelMat = _modelMat.translate(position);
	// _modelMat.rotation(rotation.Euler()).scale(scale).translate(position);
	_command->modelView = mat * _modelMat;
	renderer->addCommand(_command);
	for (auto node : children) {
		node->draw(renderer, _command->modelView);
	}
}

}