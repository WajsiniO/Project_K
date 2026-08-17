#pragma once
#include <windows.h>

enum class UIState {
    Normal,
    Hovered,
    Pressed,
    Disabled
};

struct Color {
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    unsigned char a = 255;

    COLORREF ToCOLORREF() const {
        return RGB(r, g, b);
    }
};

struct ButtonStyle {
    Color normalColor   = { 50, 50, 60, 255 };
    Color hoverColor    = { 70, 80, 110, 255 };
    Color pressedColor  = { 35, 35, 45, 255 };
    Color disabledColor = { 30, 30, 30, 255 };

    Color textColor        = { 240, 240, 240, 255 };
    Color textHoverColor   = { 255, 255, 255, 255 };

    Color borderColor      = { 100, 120, 160, 255 };
    int borderThickness    = 2;
};

struct MenuStyle {
    Color backgroundColor  = { 25, 28, 35, 255 };
    Color borderColor      = { 60, 70, 90, 255 };
    int borderThickness    = 2;

    ButtonStyle defaultButtonStyle;
};