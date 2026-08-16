#include "Window.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	Window window(L"Project_K", 1280, 720);

	if (!window.Create()) {
		return -1;
	}

	bool workingWindow = true;

	while (workingWindow) {
		workingWindow = window.Process();
	}

	return 0;
}