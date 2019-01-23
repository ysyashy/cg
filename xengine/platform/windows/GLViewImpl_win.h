#ifndef __GLVIEW_IMPL_WIN_H__
#define __GLVIEW_IMPL_WIN_H__

#include <GLFW/glfw3.h>
#include "platform/IGLView.h"
#include "math/XEMath.h"

namespace xe {

class GLEventHandler;

class GLViewImpl_win :
	public IGLView {
	friend GLEventHandler;
public:
	static IGLView *createGLView(const std::string &viewname, Rect rect = Rect::zero, bool resizable = false);
	bool initWithRect(const std::string &viewName, Rect rect, float frameZoomFactor, bool resizeable);
public:
	virtual void end() override;
	virtual bool isOpenGLReady() override;
	virtual void swapBuffers() override;
	virtual bool windowShouldClose() override;
	virtual void pullEvents() override;
private:
	GLViewImpl_win();
	virtual ~GLViewImpl_win();
	void onGLFWError(int errorId, const char *msg);
	void onGLFWMouseCallback(GLFWwindow *window, int button, int action, int modify);
	void onGLFWMouseMoveCallback(GLFWwindow *window, double x, double y);
	void onGLFWMouseScrollCallback(GLFWwindow *window, double x, double y);
	void onGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void onGLFWFramebuffersize(GLFWwindow *window, int w, int h);
	void onGLFWwindowSizeCallback(GLFWwindow *window, int w, int h);
	void onGLFWWindowIconifyCallback(GLFWwindow *window, int iconified);
private:
	GLFWwindow *glwindow = nullptr;
	GLFWmonitor *glmonitor = nullptr;
};

class GLEventHandler {
private:
	static GLViewImpl_win *glView;
public:
	static void onGLFWError(int errorId, const char* msg) {
		glView->onGLFWError(errorId, msg);
	}
	static void onGLFWMouseCallback(GLFWwindow *window, int button, int action, int modify) {
		glView->onGLFWMouseCallback(window, button, action, modify);
	}
	static void onGLFWMouseMoveCallback(GLFWwindow *window, double x, double y) {
		glView->onGLFWMouseMoveCallback(window, x, y);
	}
	static void onGLFWMouseScrollCallback(GLFWwindow *window, double x, double y) {
		glView->onGLFWMouseScrollCallback(window, x, y);
	}
	static void onGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		glView->onGLFWKeyCallback(window, key, scancode, action, mods);
	}
	static void onGLFWFramebuffersize(GLFWwindow *window, int w, int h) {
		glView->onGLFWFramebuffersize(window, w, h);
	}
	static void onGLFWwindowSizeCallback(GLFWwindow *window, int w, int h) {
		glView->onGLFWwindowSizeCallback(window, w, h);
	}
	static void onGLFWWindowIconifyCallback(GLFWwindow *window, int iconified) {
		glView->onGLFWWindowIconifyCallback(window, iconified);
	}
};

}


#endif
