#ifndef __XE_Sprite_H__
#define __XE_Sprite_H__

#include "Node.h"
#include "renderer/CommandTriangle.h"

namespace xe {

class Sprite : public Node{
public:
	virtual void draw(Renderer *renderer, const Matrix &mat, uint32_t flags) override;

protected:
	CommandTriangle triangleCommand;
};

}

#endif // !__XE_Sprite_H__
