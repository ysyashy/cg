#ifndef __XE_Renderer_H__
#define __XE_Renderer_H__

#include <vector>
#include "math/XEMath.h"

namespace xe {

class IRenderCommand;

class Renderer {
public:
	enum QUEUE_GROUP {
		GlobalZ_Group = 0,
		Opaque_3D = 1,
		Transparent_3D = 2,
		GlobalZ_Zero = 3,
		GlobalZ_Pos = 4,
		QUEUE_COUNT = 5
	};

public:
	void addCommand(IRenderCommand *command);
	void render();
	void clearGL();
	void cleanRenderCommand();
private:
	Color clearColor;
};

}

#endif // !__XE_Renderer_H__

