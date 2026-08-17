#pragma once
#include <windows.h>

class Window {
public:
    Window(const wchar_t* title, int width, int height);
    ~Window();

    bool Create();
    bool Process();

    void ToggleFullscreen();
    void SetFullscreen(bool fullscreen);
    bool IsFullscreen() const { return m_fullscreen; }

    HWND GetHWND() const { return m_hwnd; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    const wchar_t* m_title;
    int m_width;
    int m_height;
    bool m_fullscreen;
    DWORD m_savedStyle;
    WINDOWPLACEMENT m_savedPlacement;

    HWND m_hwnd;
    HINSTANCE m_hInstance;
};