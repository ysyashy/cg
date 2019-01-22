#include <Windows.h>
#include "App.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdline,
	_In_ int nCmdLine) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdline);

	// xe::Rect rect = xe::Rect::zero;
	// MessageBox(NULL, L"a", L"b", MB_OK);
	App app;
	return xe::Application::getInstance()->run();
}