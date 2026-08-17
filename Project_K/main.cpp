#include "Window.h"
#include "MenuPanel.h"
#include "UI_Style.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    // 1. Tworzymy i uruchamiamy okno gry
    Window window(L"Project K", 1280, 720);

    if (!window.Create()) {
        return -1;
    }

    HWND hwnd = window.GetHWND();

    MenuStyle darkMenuTheme;
    darkMenuTheme.backgroundColor        = { 22, 25, 32, 255 };
    darkMenuTheme.borderColor            = { 55, 65, 85, 255 };
    darkMenuTheme.borderThickness        = 2;

    darkMenuTheme.defaultButtonStyle.normalColor    = { 40, 48, 64, 255 };
    darkMenuTheme.defaultButtonStyle.hoverColor     = { 65, 80, 115, 255 };
    darkMenuTheme.defaultButtonStyle.pressedColor   = { 28, 35, 48, 255 };
    darkMenuTheme.defaultButtonStyle.textColor      = { 220, 225, 235, 255 };
    darkMenuTheme.defaultButtonStyle.textHoverColor = { 255, 255, 255, 255 };
    darkMenuTheme.defaultButtonStyle.borderColor    = { 80, 100, 140, 255 };
    darkMenuTheme.defaultButtonStyle.borderThickness= 1;

    int menuWidth = 400;
    int menuHeight = 320;
    int menuX = (window.GetWidth() - menuWidth) / 2;
    int menuY = (window.GetHeight() - menuHeight) / 2;

    MenuPanel mainMenu(menuX, menuY, menuWidth, menuHeight, darkMenuTheme);

    mainMenu.AddButton(50, 40, 300, 55, L"NOWA GRA", [hwnd]() {
        MessageBox(hwnd, L"Kliknieto: Rozpoczecie nowej gry!", L"Menu Glowne", MB_OK | MB_ICONINFORMATION);
    });

    mainMenu.AddButton(50, 120, 300, 55, L"PELNY EKRAN", [&window]() {
        window.ToggleFullscreen();
    });

    mainMenu.AddButton(50, 200, 300, 55, L"WYJSCIE", []() {
        PostQuitMessage(0);
    });

    bool workingWindow = true;

    while (workingWindow) {
        workingWindow = window.Process();

        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(hwnd, &mousePos);

        bool isLMouseDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

        //obsługa F11 pod fullscreen
        static bool wasF11Pressed = false;
        bool isF11Down = (GetAsyncKeyState(VK_F11) & 0x8000) != 0;
        if (isF11Down && !wasF11Pressed) {
            window.ToggleFullscreen();
        }
        wasF11Pressed = isF11Down;

        HDC hdc = GetDC(hwnd);
        if (hdc) {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;

            // Automatyczne centrowanie menu wzgledem biezacego rozmiaru okna/ekranu
            mainMenu.SetPosition((width - menuWidth) / 2, (height - menuHeight) / 2);

            mainMenu.Update(mousePos.x, mousePos.y, isLMouseDown);

            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP memBitmap = CreateCompatibleBitmap(hdc, width, height);
            HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

            HBRUSH bgBrush = CreateSolidBrush(RGB(12, 14, 18));
            FillRect(memDC, &clientRect, bgBrush);
            DeleteObject(bgBrush);

            mainMenu.Render(memDC);

            BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

            SelectObject(memDC, oldBitmap);
            DeleteObject(memBitmap);
            DeleteDC(memDC);
            ReleaseDC(hwnd, hdc);
        }

        Sleep(16);
    }

    return 0;
}