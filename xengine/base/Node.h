#ifndef __XE_NODE_H__
#define __XE_NODE_H__

#include <string>
#include <vector>
#include <math/XEMath.h>

namespace xe {

class Renderer;

class Node {
public:
	const std::string &getName() const;
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

public:
	// aboud render
	virtual void draw() final;
	virtual void draw(Renderer *renderer, const Matrix &mat, uint32_t flags);

	virtual void visit() final;
	virtual void visit(Renderer *renderer, const Matrix &parentMat, uint32_t flags);
protected:
	std::string name;
	Vector3 position;
	Vector3 scale;

	FQuat rotation;

	Node *parent;
	std::vector<Node*> children;
};

}

#endif // !__XE_NODE_H__
