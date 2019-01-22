#ifndef __XE_IAPPLICATION_H__
#define __XE_IAPPLICATION_H__

namespace xe {

class IApplication {
public:
	virtual bool applicationDidFinishLaunching() = 0;
	virtual void applicationDidEnterBackground() = 0;
	virtual void applicationWillEnterForeground() = 0;

	virtual void initGLContextAttrs() {}
};

}

#endif // !__XE_IAPPLICATION_H__
