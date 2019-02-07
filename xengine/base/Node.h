#ifndef __XE_NODE_H__
#define __XE_NODE_H__

#include <string>
#include <vector>
#include <math/XEMath.h>

namespace xe {

class Renderer;

class Node {
public:
	const std::string &getName() const { return name; }
	void setName(const std::string &name);

public:
	// about transform
	const Vector3 &getPosition() const;
	void setPosition(const Vector3 &pos);

	const FQuat &getRotation() const;
	void setRotation(const FQuat &quaternion);

	const Vector3 &getScale() const;
	void setScale(const Vector3 &scale);

	const Vector3 &getEulerAngles() const;
	void setEulerAngles(const Vector3 &angles);

	Node *getParent() const;
	void attachChild(Node *node);
	void detachChild(Node *node);
	const std::vector<Node*> &getChildren() const;

	Matrix getMatrix() const;

public:
	void visit(Renderer *renderer, const Matrix &mat);
	virtual void draw(Renderer *renerer, const Matrix &mat);
protected:
	std::string name;
	Vector3 position;
	Vector3 scale;

	FQuat rotation = FQuat::identify;

	Node *parent;
	std::vector<Node*> children;
};

}

#endif // !__XE_NODE_H__
