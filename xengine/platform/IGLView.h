#pragma once
#include <cinttypes>
#include <string>
#include "math/Vector2.h"

namespace xe {

struct GLContextAttrs {
	uint8_t redBits;
	uint8_t greenBits;
	uint8_t blueBits;
	uint8_t alphaBits;
	uint8_t depthBits;
	uint8_t stencilBits;
	uint8_t multisamplingCount;
};

class IGLView {
public:
	static GLContextAttrs glContextAttrs;
public:
	IGLView() {}

	virtual ~IGLView() {}
	virtual void end() = 0;
	virtual bool isOpenGLReady() = 0;
	virtual void swapBuffers() = 0;
	virtual bool windowShouldClose() = 0;
	virtual void pullEvents() = 0;

	Vector2 getFrameSize() const;
	void setFrameSize(float width, float height);

	void setViewName(const std::string &viewname);
	std::string getViewName() const;

protected:
	std::string _viewName;
	Vector2 _screenSize;
};

inline Vector2 IGLView::getFrameSize() const {
	return _screenSize;
}

inline void IGLView::setFrameSize(float width, float height) {
	_screenSize.X = width;
	_screenSize.Y = height;
}

inline void IGLView::setViewName(const std::string &viewname) {
	_viewName = viewname;
}

inline std::string IGLView::getViewName() const {
	return _viewName;
}

}