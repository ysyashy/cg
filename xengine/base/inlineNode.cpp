#include "Node.h"

namespace xe {

inline const std::string & Node::getName() const {
	return name;
}

inline void Node::setName(const std::string & name) {
	this->name = name;
}

inline const Vector3 & Node::getPosition() const {
	return position;
}

inline void Node::setPosition(const Vector3 & pos) {
	position = pos;
}

inline const FQuat & Node::getRotation() const {
	return rotation;
}

inline void Node::setRotation(const FQuat & quaternion) {
	rotation = quaternion;
}

inline const Vector3 & Node::getScale() const {
	return scale;
}

inline void Node::setScale(const Vector3 & scale) {
	this->scale = scale;
}

inline Node * Node::getParent() const {
	return parent;
}

}