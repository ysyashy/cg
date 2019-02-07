#include "RenderCommand.h"
#include "GLProgram.h"
#include "Texture2D.h"

namespace xe {

void RenderCommand::init(Type drawType, Texture2D * tex,
	GLProgram * program, 
	BlendFunc blend, 
	const VerticeList & vert, 
	const Matrix & modelMat) {

	switch (drawType) {
	case xe::RenderCommand::Type::Point:
		this->drawMode = GL_POINTS;
		break;
	case xe::RenderCommand::Type::Line:
		this->drawMode = GL_LINES;
		break;
	case xe::RenderCommand::Type::Triangle:
		this->drawMode = GL_TRIANGLES;
		break;
	default:
		break;
	}

	this->textureID = tex->getTextureId();
	this->glProgram = program;
	this->blendFunc = blend;
	this->modelView = modelMat;
	this->drawCount = vert.indexCount;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vert.indexCount * sizeof(uint16_t), vert.indices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vert.vertCount * sizeof(Vert_Color_Tex), vert.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_Color_Tex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vert_Color_Tex), (void*)sizeof(Vector3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_Color_Tex), (void*)(sizeof(Vector3) + sizeof(Color)));
	glEnableVertexAttribArray(2);
}

void RenderCommand::execute() {
	this->glProgram->use();
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(drawMode, drawCount, GL_UNSIGNED_SHORT, NULL);	
}

}