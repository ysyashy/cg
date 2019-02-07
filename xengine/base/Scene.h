#pragma once

#include <list>
#include <stack>
#include <vector>
#include <string>
#include "Node.h"
#include "math/XEMath.h"

namespace xe {

class Renderer;

class Scene {

public:
	Scene(const std::string &name);
	Vector2 getWinSize() const;
	std::string getName();
	void addChild(Node *child);
	void removeChildByName(const std::string &name);
	std::vector<Node*> getChildren();
	~Scene();
private:
	Scene();
private:
	std::string _name;
	std::vector<Node*> _children;
	Vector2 _winSize;
/********************** about renderer **************************/
public:
	void render();
private:
	Renderer * _renderer;
	Matrix _projectionMatrix;
	Matrix _viewMatrix;
};

}
