#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Window window(L"Moja pierwsza gra", 1280, 720);

	if (!window.Create()) {
		return -1; //Zwrot b³edu - nie uda³o sie uruchomiæ okna
	}

	bool workingWindow = true;

	while (workingWindow) {
		workingWindow = window.Process();
	}
}