#ifndef __XE_Sprite_H__
#define __XE_Sprite_H__

#include "math/XEMath.h"
#include "Node.h"
#include "xeTypes.h"
#include "renderer/Texture2D.h"


namespace xe {

class RenderCommand;
class GLProgram;

class Sprite : public Node{
public:
	Sprite(Texture2D *texture);
	virtual ~Sprite();
	Vector2 getSize() const;
private:
	Sprite() {}
	void init();
public:
	virtual void draw(Renderer *renderer, const Matrix &mat) override;
protected:
	Texture2D *_texture;
	VerticeList vert;
private:
	GLProgram *_program;
	RenderCommand * _command;
	Matrix _modelMat;
};

}

#endif // !__XE_Sprite_H__
