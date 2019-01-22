#ifndef __XE_DIRECTOR_H__
#define __XE_DIRECTOR_H__

#include "platform/IGLView.h"

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
};

}


#endif