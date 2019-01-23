#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
#include "GLViewImpl_win.h"
#include "event/XEEvent.h"
#include "../Application.h"

namespace xe {

GLViewImpl_win* GLEventHandler::glView = nullptr;

struct keyCodeItem {
	int glfwKeyCode;
	EventKeyboard::KeyCode keyCode;
};

static std::unordered_map<int, EventKeyboard::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
	/* The unknown key */
	{ GLFW_KEY_UNKNOWN         , EventKeyboard::KeyCode::KEY_NONE          },

	/* Printable keys */
	{ GLFW_KEY_SPACE           , EventKeyboard::KeyCode::KEY_SPACE         },
	{ GLFW_KEY_APOSTROPHE      , EventKeyboard::KeyCode::KEY_APOSTROPHE    },
	{ GLFW_KEY_COMMA           , EventKeyboard::KeyCode::KEY_COMMA         },
	{ GLFW_KEY_MINUS           , EventKeyboard::KeyCode::KEY_MINUS         },
	{ GLFW_KEY_PERIOD          , EventKeyboard::KeyCode::KEY_PERIOD        },
	{ GLFW_KEY_SLASH           , EventKeyboard::KeyCode::KEY_SLASH         },
	{ GLFW_KEY_0               , EventKeyboard::KeyCode::KEY_0             },
	{ GLFW_KEY_1               , EventKeyboard::KeyCode::KEY_1             },
	{ GLFW_KEY_2               , EventKeyboard::KeyCode::KEY_2             },
	{ GLFW_KEY_3               , EventKeyboard::KeyCode::KEY_3             },
	{ GLFW_KEY_4               , EventKeyboard::KeyCode::KEY_4             },
	{ GLFW_KEY_5               , EventKeyboard::KeyCode::KEY_5             },
	{ GLFW_KEY_6               , EventKeyboard::KeyCode::KEY_6             },
	{ GLFW_KEY_7               , EventKeyboard::KeyCode::KEY_7             },
	{ GLFW_KEY_8               , EventKeyboard::KeyCode::KEY_8             },
	{ GLFW_KEY_9               , EventKeyboard::KeyCode::KEY_9             },
	{ GLFW_KEY_SEMICOLON       , EventKeyboard::KeyCode::KEY_SEMICOLON     },
	{ GLFW_KEY_EQUAL           , EventKeyboard::KeyCode::KEY_EQUAL         },
	{ GLFW_KEY_A               , EventKeyboard::KeyCode::KEY_A             },
	{ GLFW_KEY_B               , EventKeyboard::KeyCode::KEY_B             },
	{ GLFW_KEY_C               , EventKeyboard::KeyCode::KEY_C             },
	{ GLFW_KEY_D               , EventKeyboard::KeyCode::KEY_D             },
	{ GLFW_KEY_E               , EventKeyboard::KeyCode::KEY_E             },
	{ GLFW_KEY_F               , EventKeyboard::KeyCode::KEY_F             },
	{ GLFW_KEY_G               , EventKeyboard::KeyCode::KEY_G             },
	{ GLFW_KEY_H               , EventKeyboard::KeyCode::KEY_H             },
	{ GLFW_KEY_I               , EventKeyboard::KeyCode::KEY_I             },
	{ GLFW_KEY_J               , EventKeyboard::KeyCode::KEY_J             },
	{ GLFW_KEY_K               , EventKeyboard::KeyCode::KEY_K             },
	{ GLFW_KEY_L               , EventKeyboard::KeyCode::KEY_L             },
	{ GLFW_KEY_M               , EventKeyboard::KeyCode::KEY_M             },
	{ GLFW_KEY_N               , EventKeyboard::KeyCode::KEY_N             },
	{ GLFW_KEY_O               , EventKeyboard::KeyCode::KEY_O             },
	{ GLFW_KEY_P               , EventKeyboard::KeyCode::KEY_P             },
	{ GLFW_KEY_Q               , EventKeyboard::KeyCode::KEY_Q             },
	{ GLFW_KEY_R               , EventKeyboard::KeyCode::KEY_R             },
	{ GLFW_KEY_S               , EventKeyboard::KeyCode::KEY_S             },
	{ GLFW_KEY_T               , EventKeyboard::KeyCode::KEY_T             },
	{ GLFW_KEY_U               , EventKeyboard::KeyCode::KEY_U             },
	{ GLFW_KEY_V               , EventKeyboard::KeyCode::KEY_V             },
	{ GLFW_KEY_W               , EventKeyboard::KeyCode::KEY_W             },
	{ GLFW_KEY_X               , EventKeyboard::KeyCode::KEY_X             },
	{ GLFW_KEY_Y               , EventKeyboard::KeyCode::KEY_Y             },
	{ GLFW_KEY_Z               , EventKeyboard::KeyCode::KEY_Z             },
	{ GLFW_KEY_LEFT_BRACKET    , EventKeyboard::KeyCode::KEY_LEFT_BRACKET  },
	{ GLFW_KEY_BACKSLASH       , EventKeyboard::KeyCode::KEY_BACK_SLASH    },
	{ GLFW_KEY_RIGHT_BRACKET   , EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
	{ GLFW_KEY_GRAVE_ACCENT    , EventKeyboard::KeyCode::KEY_GRAVE         },
	{ GLFW_KEY_WORLD_1         , EventKeyboard::KeyCode::KEY_GRAVE         },
	{ GLFW_KEY_WORLD_2         , EventKeyboard::KeyCode::KEY_NONE          },

	/* Function keys */
	{ GLFW_KEY_ESCAPE          , EventKeyboard::KeyCode::KEY_ESCAPE        },
	{ GLFW_KEY_ENTER           , EventKeyboard::KeyCode::KEY_ENTER      },
	{ GLFW_KEY_TAB             , EventKeyboard::KeyCode::KEY_TAB           },
	{ GLFW_KEY_BACKSPACE       , EventKeyboard::KeyCode::KEY_BACKSPACE     },
	{ GLFW_KEY_INSERT          , EventKeyboard::KeyCode::KEY_INSERT        },
	{ GLFW_KEY_DELETE          , EventKeyboard::KeyCode::KEY_DELETE        },
	{ GLFW_KEY_RIGHT           , EventKeyboard::KeyCode::KEY_RIGHT_ARROW   },
	{ GLFW_KEY_LEFT            , EventKeyboard::KeyCode::KEY_LEFT_ARROW    },
	{ GLFW_KEY_DOWN            , EventKeyboard::KeyCode::KEY_DOWN_ARROW    },
	{ GLFW_KEY_UP              , EventKeyboard::KeyCode::KEY_UP_ARROW      },
	{ GLFW_KEY_PAGE_UP         , EventKeyboard::KeyCode::KEY_PG_UP      },
	{ GLFW_KEY_PAGE_DOWN       , EventKeyboard::KeyCode::KEY_PG_DOWN    },
	{ GLFW_KEY_HOME            , EventKeyboard::KeyCode::KEY_HOME       },
	{ GLFW_KEY_END             , EventKeyboard::KeyCode::KEY_END           },
	{ GLFW_KEY_CAPS_LOCK       , EventKeyboard::KeyCode::KEY_CAPS_LOCK     },
	{ GLFW_KEY_SCROLL_LOCK     , EventKeyboard::KeyCode::KEY_SCROLL_LOCK   },
	{ GLFW_KEY_NUM_LOCK        , EventKeyboard::KeyCode::KEY_NUM_LOCK      },
	{ GLFW_KEY_PRINT_SCREEN    , EventKeyboard::KeyCode::KEY_PRINT         },
	{ GLFW_KEY_PAUSE           , EventKeyboard::KeyCode::KEY_PAUSE         },
	{ GLFW_KEY_F1              , EventKeyboard::KeyCode::KEY_F1            },
	{ GLFW_KEY_F2              , EventKeyboard::KeyCode::KEY_F2            },
	{ GLFW_KEY_F3              , EventKeyboard::KeyCode::KEY_F3            },
	{ GLFW_KEY_F4              , EventKeyboard::KeyCode::KEY_F4            },
	{ GLFW_KEY_F5              , EventKeyboard::KeyCode::KEY_F5            },
	{ GLFW_KEY_F6              , EventKeyboard::KeyCode::KEY_F6            },
	{ GLFW_KEY_F7              , EventKeyboard::KeyCode::KEY_F7            },
	{ GLFW_KEY_F8              , EventKeyboard::KeyCode::KEY_F8            },
	{ GLFW_KEY_F9              , EventKeyboard::KeyCode::KEY_F9            },
	{ GLFW_KEY_F10             , EventKeyboard::KeyCode::KEY_F10           },
	{ GLFW_KEY_F11             , EventKeyboard::KeyCode::KEY_F11           },
	{ GLFW_KEY_F12             , EventKeyboard::KeyCode::KEY_F12           },
	{ GLFW_KEY_F13             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F14             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F15             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F16             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F17             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F18             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F19             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F20             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F21             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F22             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F23             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F24             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_F25             , EventKeyboard::KeyCode::KEY_NONE          },
	{ GLFW_KEY_KP_0            , EventKeyboard::KeyCode::KEY_0             },
	{ GLFW_KEY_KP_1            , EventKeyboard::KeyCode::KEY_1             },
	{ GLFW_KEY_KP_2            , EventKeyboard::KeyCode::KEY_2             },
	{ GLFW_KEY_KP_3            , EventKeyboard::KeyCode::KEY_3             },
	{ GLFW_KEY_KP_4            , EventKeyboard::KeyCode::KEY_4             },
	{ GLFW_KEY_KP_5            , EventKeyboard::KeyCode::KEY_5             },
	{ GLFW_KEY_KP_6            , EventKeyboard::KeyCode::KEY_6             },
	{ GLFW_KEY_KP_7            , EventKeyboard::KeyCode::KEY_7             },
	{ GLFW_KEY_KP_8            , EventKeyboard::KeyCode::KEY_8             },
	{ GLFW_KEY_KP_9            , EventKeyboard::KeyCode::KEY_9             },
	{ GLFW_KEY_KP_DECIMAL      , EventKeyboard::KeyCode::KEY_PERIOD        },
	{ GLFW_KEY_KP_DIVIDE       , EventKeyboard::KeyCode::KEY_KP_DIVIDE     },
	{ GLFW_KEY_KP_MULTIPLY     , EventKeyboard::KeyCode::KEY_KP_MULTIPLY   },
	{ GLFW_KEY_KP_SUBTRACT     , EventKeyboard::KeyCode::KEY_KP_MINUS      },
	{ GLFW_KEY_KP_ADD          , EventKeyboard::KeyCode::KEY_KP_PLUS       },
	{ GLFW_KEY_KP_ENTER        , EventKeyboard::KeyCode::KEY_KP_ENTER      },
	{ GLFW_KEY_KP_EQUAL        , EventKeyboard::KeyCode::KEY_EQUAL         },
	{ GLFW_KEY_LEFT_SHIFT      , EventKeyboard::KeyCode::KEY_LEFT_SHIFT         },
	{ GLFW_KEY_LEFT_CONTROL    , EventKeyboard::KeyCode::KEY_LEFT_CTRL          },
	{ GLFW_KEY_LEFT_ALT        , EventKeyboard::KeyCode::KEY_LEFT_ALT           },
	{ GLFW_KEY_LEFT_SUPER      , EventKeyboard::KeyCode::KEY_HYPER         },
	{ GLFW_KEY_RIGHT_SHIFT     , EventKeyboard::KeyCode::KEY_RIGHT_SHIFT         },
	{ GLFW_KEY_RIGHT_CONTROL   , EventKeyboard::KeyCode::KEY_RIGHT_CTRL          },
	{ GLFW_KEY_RIGHT_ALT       , EventKeyboard::KeyCode::KEY_RIGHT_ALT           },
	{ GLFW_KEY_RIGHT_SUPER     , EventKeyboard::KeyCode::KEY_HYPER         },
	{ GLFW_KEY_MENU            , EventKeyboard::KeyCode::KEY_MENU          },
	{ GLFW_KEY_LAST            , EventKeyboard::KeyCode::KEY_NONE          }
};

GLViewImpl_win::GLViewImpl_win() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(GLEventHandler::onGLFWError);
}

GLViewImpl_win::~GLViewImpl_win() {}

bool GLViewImpl_win::initWithRect(const std::string & viewName, Rect rect, float frameZoomFactor, bool resizeable) {
	setViewName(viewName);
	glmonitor = glfwGetPrimaryMonitor();
	if (nullptr == glmonitor) { return false; }
	if (rect == Rect::zero) {
		const GLFWvidmode *videoMode = glfwGetVideoMode(glmonitor);
		rect = Rect(0, 0, (float)videoMode->width / 2, (float)videoMode->height / 2);
	}
	setFrameSize(rect.W, rect.H);

	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);

	glfwWindowHint(GLFW_RED_BITS, glContextAttrs.redBits);
	glfwWindowHint(GLFW_GREEN_BITS, glContextAttrs.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, glContextAttrs.blueBits);
	glfwWindowHint(GLFW_ALPHA_BITS, glContextAttrs.alphaBits);
	glfwWindowHint(GLFW_DEPTH_BITS, glContextAttrs.depthBits);
	glfwWindowHint(GLFW_STENCIL_BITS, glContextAttrs.stencilBits);

	glfwWindowHint(GLFW_SAMPLES, glContextAttrs.multisamplingCount);

	float neededWidth = rect.W * frameZoomFactor;
	float neededHeight = rect.H * frameZoomFactor;

	// glwindow = glfwCreateWindow((int)neededWidth, (int)neededHeight, viewName.c_str(), glmonitor, nullptr);
	glwindow = glfwCreateWindow((int)neededWidth, (int)neededHeight, viewName.c_str(), nullptr, nullptr);
	if (glwindow == nullptr) {
		std::string msg = "Can't create window";
		std::cerr << msg << std::endl;
		return false;
	}
	glfwSetWindowPos(glwindow, (int)rect.X, (int)rect.Y);
	glfwMakeContextCurrent(glwindow);

	// add glfw callback
	glfwSetMouseButtonCallback(glwindow, GLEventHandler::onGLFWMouseCallback);
	glfwSetCursorPosCallback(glwindow, GLEventHandler::onGLFWMouseMoveCallback);
	glfwSetScrollCallback(glwindow, GLEventHandler::onGLFWMouseScrollCallback);
	glfwSetKeyCallback(glwindow, GLEventHandler::onGLFWKeyCallback);
	glfwSetFramebufferSizeCallback(glwindow, GLEventHandler::onGLFWFramebuffersize);
	glfwSetWindowSizeCallback(glwindow, GLEventHandler::onGLFWwindowSizeCallback);

	// init glew
	if (GLEW_OK != glewInit()) {
		std::cerr << "GLEW init error." << std::endl;
		return false;
	}

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	if (glContextAttrs.multisamplingCount > 0) {
		glEnable(GL_MULTISAMPLE);
	}

	return true;
}

IGLView * GLViewImpl_win::createGLView(const std::string & viewname, Rect rect, bool resizable) {
	GLViewImpl_win *view = new (std::nothrow) GLViewImpl_win();
	if (nullptr != view && view->initWithRect(viewname, rect, 1.0f, resizable)) {
		return view;
	}
	if (nullptr != view) { delete view; }
	return nullptr;
}

void GLViewImpl_win::onGLFWError(int errorId, const char *msg) {
	std::cerr << msg << std::endl;
}
void GLViewImpl_win::onGLFWMouseCallback(GLFWwindow *window, int button, int action, int modify) {
}
void GLViewImpl_win::onGLFWMouseMoveCallback(GLFWwindow *window, double x, double y) {

}
void GLViewImpl_win::onGLFWMouseScrollCallback(GLFWwindow *window, double x, double y) {

}
void GLViewImpl_win::onGLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

}
void GLViewImpl_win::onGLFWFramebuffersize(GLFWwindow *window, int w, int h) {

}
void GLViewImpl_win::onGLFWwindowSizeCallback(GLFWwindow *window, int w, int h) {

}

void GLViewImpl_win::onGLFWWindowIconifyCallback(GLFWwindow * window, int iconified) {
	if (iconified == GL_TRUE) {
		Application::getInstance()->applicationDidEnterBackground();
	} else {
		Application::getInstance()->applicationWillEnterForeground();
	}
}

void GLViewImpl_win::end() {
	if(nullptr != glwindow){
		glfwSetWindowShouldClose(glwindow, 1);
		glwindow = nullptr;
	}
}

bool GLViewImpl_win::isOpenGLReady() {
	return nullptr != glwindow;
}

void GLViewImpl_win::swapBuffers() {
	if (glwindow) { glfwSwapBuffers(glwindow); }
}

bool GLViewImpl_win::windowShouldClose() {
	return nullptr != glwindow && glfwWindowShouldClose(glwindow);
}

void GLViewImpl_win::pullEvents() {
	glfwPollEvents();
}

}

