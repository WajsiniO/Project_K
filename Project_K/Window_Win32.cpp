#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(const wchar_t* title, int width, int height) : m_title(title), m_width(width), m_height(height), m_hwnd(nullptr) {
    m_hInstance = GetModuleHandle(nullptr);
}

Window::~Window() {
    if (m_hwnd != nullptr) {
        DestroyWindow(m_hwnd);
    }
}

bool Window::Create() {
    const wchar_t* classTitle = L"Class Project_K";

    WNDCLASSEX wnd;

    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.style = CS_OWNDC;
    wnd.lpfnWndProc = WindowProc;
    wnd.hInstance = m_hInstance;
    wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wnd.lpszClassName = classTitle;

    if (!RegisterClassEx(&wnd)) {
        return false;
    }

    //tworzenie okna
    m_hwnd = CreateWindowEx(
        0,
        classTitle,
        m_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_width, m_height,
        nullptr, nullptr, m_hInstance, nullptr
    );

    if (m_hwnd == nullptr) {
        return false; //zwrot b³êdu
    }

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    return true;
}

bool Window::Process() {
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            return false; //zamkniêcie progamu
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}