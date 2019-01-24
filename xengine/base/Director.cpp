#include <iostream>

#include "platform/IGLView.h"
#include "renderer/Renderer.h"
#include "Director.h"

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

Director::Director() : glview(nullptr) {}

bool Director::init() {
	return true;
}

void Director::tick() {

	if (glview) {
		glview->pullEvents();
	}

	renderer->clear();
	FrameBuffer::clearAllFBOS();

	pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	render->clearDrawStats();
	if (glview) {
		glview->renderScene(scene, render);
	}
	updateFrameRate();

	render->render();

	popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	if (glview != nullptr) {
		glview->swapBuffers();
	}
}

Director::~Director() {}

void Director::pushMatrix(MATRIX_STACK_TYPE type) {
}

void Director::popMatrix(MATRIX_STACK_TYPE type) {
}

}