#include "Button.h"

Button::Button(int x, int y, int width, int height, const wchar_t* text, UI_Components* parent)
    : UI_Components(x, y, width, height, parent), m_text(text != nullptr ? text : L""), m_wasPressed(false) {
}

Button::~Button() {
}

void Button::Update(int mouseX, int mouseY, bool isMouseDown) {
    if (!m_isVisible || m_state == UIState::Disabled) return;

    bool inside = IsPointInside(mouseX, mouseY);

    if (inside) {
        if (isMouseDown) {
            m_state = UIState::Pressed;
            m_wasPressed = true;
        } else {
            if (m_wasPressed) {
                m_wasPressed = false;
                if (m_onClick) {
                    m_onClick();
                }
            }
            m_state = UIState::Hovered;
        }
    } else {
        m_wasPressed = false;
        m_state = UIState::Normal;
    }
}

void Button::Render(HDC hdc) {
    if (!m_isVisible) return;

    int gx = GetGlobalX();
    int gy = GetGlobalY();
    RECT rect = { gx, gy, gx + m_width, gy + m_height };

    Color bgColor = m_style.normalColor;
    Color txtColor = m_style.textColor;

    switch (m_state) {
        case UIState::Hovered:
            bgColor = m_style.hoverColor;
            txtColor = m_style.textHoverColor;
            break;
        case UIState::Pressed:
            bgColor = m_style.pressedColor;
            txtColor = m_style.textHoverColor;
            break;
        case UIState::Disabled:
            bgColor = m_style.disabledColor;
            break;
        default:
            break;
    }

    HBRUSH bgBrush = CreateSolidBrush(bgColor.ToCOLORREF());
    FillRect(hdc, &rect, bgBrush);
    DeleteObject(bgBrush);

    if (m_style.borderThickness > 0) {
        HBRUSH borderBrush = CreateSolidBrush(m_style.borderColor.ToCOLORREF());
        FrameRect(hdc, &rect, borderBrush);
        DeleteObject(borderBrush);
    }

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, txtColor.ToCOLORREF());
    DrawTextW(hdc, m_text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}