#include <iostream>

#include "platform/IGLView.h"
#include "Director.h"
#include "base/Scene.h"

namespace xe {

const int kDefaultFPS = 60;

Director *Director::instance = nullptr;

Director * Director::getInstance() {
	if (nullptr == instance) {
		instance = new (std::nothrow) Director();
		instance->init();
	}
	return instance;
}

void Director::destroyInstance() {
	if (instance != nullptr) {
		delete instance;
	}
}

Vector2 Director::getWinSize() const {
	if (nullptr != glview) {
		return glview->getFrameSize();
	} else {
		return Vector2(0.0f, 0.0f);
	}
}

void Director::end() {}

void Director::mainLoop() {
	tick();
}

IGLView * Director::getGLView() {
	return glview;
}

void Director::setGLView(IGLView * view) {
	glview = view;
}

Scene * Director::getScene() {
	return currScene;
}

void Director::setScene(Scene * scene) {
	currScene = scene;
}

Director::Director() : glview(nullptr) {}

bool Director::init() {
	return true;
}

void Director::tick() {

	if (glview) {
		glview->pullEvents();
	}

	if (nullptr != currScene) {
		currScene->render();
	}

	if (glview != nullptr) {
		glview->swapBuffers();
	}
}

Director::~Director() {}

}