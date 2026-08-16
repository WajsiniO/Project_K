#pragma once
#include <windows.h>

class Window {
	public:
		Window(const wchar_t* title, int width, int height);
		~Window();

		bool Create();
		bool Process();

	private:
		const wchar_t* m_title;
		int m_width;
		int m_height;

		HWND m_hwnd;
		HINSTANCE m_hInstance;
};