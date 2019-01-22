#pragma once

#include "platform/Application.h"

class App : public xe::Application {
public:
	virtual bool applicationDidFinishLaunching() override;
	virtual void applicationDidEnterBackground() override;
	virtual void applicationWillEnterForeground() override;
	virtual void initGLContextAttrs() override;

	App();
	~App();
};

