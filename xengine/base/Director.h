#ifndef __XE_DIRECTOR_H__
#define __XE_DIRECTOR_H__

#include <stack>
#include "math/Matrix.h"

namespace xe {

class IGLView;
class Scene;

enum class MATRIX_STACK_TYPE {
	MATRIX_STACK_MODELVIEW,
	MATRIX_STACK_PROJECTION,
	MATRIX_STACK_TEXTURE
};

class Director {
public:
	static Director *getInstance();
	static void destroyInstance();

	Vector2 getWinSize() const;
	void end();
	void mainLoop();
	IGLView *getGLView();
	void setGLView(IGLView *view);
	Scene *getScene();
	void setScene(Scene *scene);
	bool init();
	void tick();
private:
	static Director *instance;
	Director();
	virtual ~Director();
private:
	IGLView *glview;
	Scene *currScene;
};

}


#endif