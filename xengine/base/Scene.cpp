#include <algorithm>
#include <cassert>
#include <iostream>

#include "Scene.h"
#include "Director.h"
#include "renderer/Renderer.h"
#include "Node.h"

namespace xe {

Scene::Scene() {
}

void Scene::render() {
	_renderer = new Renderer();
	_viewMatrix = Matrix::identify;
	_projectionMatrix = Matrix::identify;
	Matrix pvmMat = _projectionMatrix * _viewMatrix;
	// visit and renderer
	_renderer->clear();
	for (auto iter = _children.cbegin(); iter != _children.cend(); iter++) {
		(*iter)->visit(_renderer, pvmMat);
	}
	_renderer->renderer();
}

Scene::Scene(const std::string & name)
	: _name(name){
	_winSize = Director::getInstance()->getWinSize();
}

inline Vector2 Scene::getWinSize() const {
	return _winSize;
}

inline std::string Scene::getName() {
	return _name;
}

void Scene::addChild(Node * child) {
	assert(nullptr != child, "child is null");
	assert(!child->getName().empty(), "child name is not allow empty!");
	bool isExist = false;
	for (Node *node : _children) {
		if (node->getName() == child->getName()) { 
			isExist = true;
			break;
		}
	}
	assert(!isExist, "node is exists");
	_children.push_back(child);
}

void Scene::removeChildByName(const std::string & name) {
	if (name.empty()) { return; }
	std::vector<Node*>::iterator iter = _children.begin();
	for (; iter != _children.end(); iter++) {
		if ((*iter)->getName() == name) { break; }
	}
	if (iter != _children.end()) { _children.erase(iter); }
	else { std::cout << "node not exists: " << name << std::endl; }
}

inline std::vector<Node*> Scene::getChildren() {
	return _children;
}

Scene::~Scene() {
	for (auto child : _children) {
		delete child;
	}
	_children.clear();
}

}