#include <iostream>


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

void Director::mainLoop() {}

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

}



Director::~Director() {}

}