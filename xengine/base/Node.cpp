#include <cassert>
#include "Node.h"
#include "math/XEMath.h"


namespace xe {

void Node::visit(Renderer * renderer, const Matrix & mat) {
	draw(renderer, mat);
	if (!children.empty()) {
		Matrix m = mat * getMatrix();
		for (auto child : children) {
			child->visit(renderer, m);
		}
	}
}

void Node::draw(Renderer * renerer, const Matrix & mat) {
	// null Node, do nothing
}


void Node::attachChild(Node * node) {
	if (nullptr != node) {
		children.push_back(node);
	}
}

void Node::detachChild(Node * node) {
	if (nullptr == node) { return; }
	auto iter = children.begin();
	for (; iter != children.end(); iter++) {
		if (node->getName() == (*iter)->getName()) { break; }
	}
	if (iter != children.end()) {
		children.erase(iter);
	}
}

const Vector3 & Node::getEulerAngles() const {
	return rotation.Euler();
}

void Node::setEulerAngles(const Vector3 & angles) {
	rotation = FQuat::MakeFromEuler(angles);
}

Matrix Node::getMatrix() const {
	return rotation.makeMatrix().scale(scale).translate(position);
}

void Node::setName(const std::string & name) {
	this->name = name;
}

inline const Vector3 & Node::getPosition() const {
	return position;
}

void Node::setPosition(const Vector3 & pos) {
	position = pos;
}

inline const FQuat & Node::getRotation() const {
	return rotation;
}

void Node::setRotation(const FQuat & quaternion) {
	rotation = quaternion;
}

inline const Vector3 & Node::getScale() const {
	return scale;
}

void Node::setScale(const Vector3 & scale) {
	this->scale = scale;
}

inline Node * Node::getParent() const {
	return parent;
}
const std::vector<Node*>& Node::getChildren() const {
	return children;
}


}