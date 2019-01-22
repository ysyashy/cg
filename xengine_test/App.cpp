#include "App.h"
#include "platform/IGLView.h"
#include "platform/windows/GLViewImpl_win.h"
#include "base/Director.h"
#include "math/XEMath.h"

void App::initGLContextAttrs() {
	xe::GLContextAttrs glContext = { 8, 8, 8, 8, 24, 8, 0 };
	xe::IGLView::glContextAttrs = glContext;
}

bool App::applicationDidFinishLaunching() {
	auto director = xe::Director::getInstance();
	auto glview = director->getGLView();
	if (nullptr == glview) {
		glview = xe::GLViewImpl_win::createGLView("CG", xe::Rect(50, 50, 800, 600));
		director->setGLView(glview);
	}
	return true;
}

void App::applicationDidEnterBackground() {}

void App::applicationWillEnterForeground() {}



App::App() {}


App::~App() {}
