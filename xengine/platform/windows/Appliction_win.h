#ifndef __XE_APPLICATION_WIN_H__
#define __XE_APPLICATION_WIN_H__

#include <string>
#include <Windows.h>
#include "platform/IApplication.h"

namespace xe {

class Application : public IApplication{
public:
	static Application *getInstance();
public:
	Application();
	virtual ~Application();
	int run();
public:
	virtual bool applicationDidFinishLaunching() = 0;
	virtual void applicationDidEnterBackground() = 0;
	virtual void applicationWillEnterForeground() = 0;
private:
	HINSTANCE instance;
	HACCEL accelTable;
	LARGE_INTEGER fpsInterval;
	std::string resPath;

	static Application *pSharedApplication;
};

}

#endif // !__XE_APPLICATION_H__
