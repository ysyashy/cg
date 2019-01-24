#include "renderer/Renderer.h"
#include "Node.h"


namespace xe {


void Node::attachChild(Node * node) {
}

void Node::detachChild(Node * node) {
}

void Node::draw() {}

void Node::draw(Renderer * renderer, const Matrix & mat, uint32_t flags) {}

void Node::visit() {}

void Node::visit(Renderer * renderer, const Matrix & parentMat, uint32_t flags) {}

const Vector3 & Node::getEulerAngles() const {
	return rotation.Euler();
}

void Node::setEulerAngles(const Vector3 & angles) {
	rotation = FQuat::MakeFromEuler(angles);
}

}