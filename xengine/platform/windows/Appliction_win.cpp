#include <Windows.h>
#include <timeapi.h>
#include <cassert>
#include <algorithm>

#include "base/Director.h"
#include "Appliction_win.h"
#include "GLViewImpl_win.h"

namespace xe {

Application *Application::pSharedApplication = nullptr;

Application::Application() 
	: instance(nullptr), accelTable(nullptr) {
	instance = GetModuleHandle(nullptr);
	fpsInterval.QuadPart = 0;
	
	assert(nullptr == pSharedApplication, "app is not null");
	pSharedApplication = this;
}

Application * Application::getInstance() {
	assert(pSharedApplication != nullptr, "app is null");
	return pSharedApplication;
}

Application::~Application() {
	assert(this == pSharedApplication, "app is not exist");
	pSharedApplication = nullptr;
}

int Application::run() {
	UINT TARGET_RESOLUTION = 1;
	TIMECAPS tc;
	UINT wTimerRes = 0;
	if (TIMERR_NOCANDO == timeGetDevCaps(&tc, sizeof(TIMECAPS))) {
		wTimerRes = std::min<UINT>(std::max<UINT>(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
		timeBeginPeriod(wTimerRes);
	}

	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	QueryPerformanceCounter(&nLast);

	initGLContextAttrs();

	if (!applicationDidFinishLaunching()) {
		return 1;
	}

	Director *director = Director::getInstance();
	IGLView *glview = director->getGLView();

	LONGLONG interval = 0LL;
	LONG waitMS = 0L;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	while (!glview->windowShouldClose()) {
		QueryPerformanceCounter(&nNow);
		interval = nNow.QuadPart - nLast.QuadPart;
		if (interval >= fpsInterval.QuadPart) {
			nLast.QuadPart = nNow.QuadPart;
			director->mainLoop();
			glview->pullEvents();
		} else {
			waitMS = (fpsInterval.QuadPart - interval) * 1000LL / freq.QuadPart - 1L;
			if (waitMS > 1L) {
				Sleep(waitMS);
			}
		}
	}

	if (glview->isOpenGLReady()) {
		director->end();
		director->mainLoop();
		director->destroyInstance();
	}

	delete glview;

	return 0;
}

}