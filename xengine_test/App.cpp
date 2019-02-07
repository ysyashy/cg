#include <GL/glew.h>
#include "App.h"
#include "platform/IGLView.h"
#include "platform/windows/GLViewImpl_win.h"
#include "base/Director.h"
#include "math/XEMath.h"
#include "base/Scene.h"
#include "base/Sprite.h"

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
	xe::Scene *scene = new xe::Scene("rootScene");
	director->setScene(scene);
	xe::Texture2D *tex1 = new xe::Texture2D("textures/awesomeface.png");
	xe::Sprite *spr = new xe::Sprite(tex1);
	spr->setScale(xe::Vector3(1.2f, 1.5f, 1.0f));
	// spr->setRotation(xe::FQuat(0.71f, 0.71f, 0.71f, 0.71f));
	spr->setEulerAngles(xe::Vector3(90.0f, 90.0f, 90.0f));
	// spr->setPosition(xe::Vector3(0.5f, -0.4f, 0.0f));
	spr->setName("spr1");
	scene->addChild(spr);
	return true;
}

void App::applicationDidEnterBackground() {}

void App::applicationWillEnterForeground() {}



App::App() {}


App::~App() {}
