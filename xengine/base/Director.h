#ifndef __XE_DIRECTOR_H__
#define __XE_DIRECTOR_H__

#include <stack>
#include "platform/IGLView.h"
#include "math/Matrix.h"

namespace xe {

enum class MATRIX_STACK_TYPE {
	MATRIX_STACK_MODELVIEW,
	MATRIX_STACK_PROJECTION,
	MATRIX_STACK_TEXTURE
};

class Director {
public:
	static Director *getInstance();
	static void destroyInstance();

	void end();
	void mainLoop();
	IGLView *getGLView();
	void setGLView(IGLView *view);
	bool init();
	void tick();
private:
	static Director *instance;
	Director();
	virtual ~Director();
private:
	IGLView *glview;
private:
	std::stack<Matrix> modelViewMatrixStack;
	std::stack<Matrix> projectionMatrix;
	std::stack<Matrix> textureMatrixStack;
public:
	void pushMatrix(MATRIX_STACK_TYPE type);
	void popMatrix(MATRIX_STACK_TYPE type);
};

}


#endif