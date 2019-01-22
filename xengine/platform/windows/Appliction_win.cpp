#include <Windows.h>
#include <timeapi.h>
#include <cassert>
#include <algorithm>

#include "base/Director.h"
#include "Appliction_win.h"
#include "GLViewImpl_win.h"

namespace xe {

static void PVRFrameEnableControlWindow(bool bEnable);

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
	PVRFrameEnableControlWindow(false);

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

void Application::applicationDidEnterBackground() {}

void Application::applicationWillEnterForeground() {}

void PVRFrameEnableControlWindow(bool bEnable) {
	HKEY hKey = 0;

	// Open PVRFrame control key, if not exists create it.
	if (ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
		L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		0,
		&hKey,
		nullptr)) {
		return;
	}
	const WCHAR *wszValue = L"hide_gui";
	const WCHAR *wszNewData = (bEnable) ? L"NO" : L"YES";
	WCHAR wszOldData[256] = { 0 };
	DWORD dwSize = sizeof(wszOldData);
	LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, nullptr, (LPBYTE)wszOldData, &dwSize);
	if (ERROR_FILE_NOT_FOUND == status
		|| (ERROR_SUCCESS == status && 0 != wcscmp(wszNewData, wszOldData))) {
		dwSize = sizeof(WCHAR) * (wcslen(wszNewData) + 1);
		RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE *)wszNewData, dwSize);
	}
	RegCloseKey(hKey);
}

}