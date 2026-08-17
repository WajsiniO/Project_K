#include "MenuPanel.h"

MenuPanel::MenuPanel(int x, int y, int width, int height, const MenuStyle& style, UI_Components* parent)
    : UI_Container(x, y, width, height, parent), m_menuStyle(style) {
}

MenuPanel::~MenuPanel() {
}

Button* MenuPanel::AddButton(int x, int y, int width, int height, const wchar_t* text, std::function<void()> onClick) {
    Button* button = new Button(x, y, width, height, text, this);
    button->SetStyle(m_menuStyle.defaultButtonStyle);

    if (onClick != nullptr) {
        button->SetOnClick(onClick);
    }

    AddChild(button);

    return button;
}

void MenuPanel::SetMenuStyle(const MenuStyle& style) {
    m_menuStyle = style;

    for (UI_Components* child : m_children) {
        Button* btn = dynamic_cast<Button*>(child);
        if (btn != nullptr) {
            btn->SetStyle(m_menuStyle.defaultButtonStyle);
        }
    }
}

void MenuPanel::Render(HDC hdc) {
    if (!m_isVisible) return;

    int gx = GetGlobalX();
    int gy = GetGlobalY();
    RECT rect = { gx, gy, gx + m_width, gy + m_height };

    HBRUSH bgBrush = CreateSolidBrush(m_menuStyle.backgroundColor.ToCOLORREF());
    FillRect(hdc, &rect, bgBrush);
    DeleteObject(bgBrush);


    if (m_menuStyle.borderThickness > 0) {
        HBRUSH borderBrush = CreateSolidBrush(m_menuStyle.borderColor.ToCOLORREF());
        FrameRect(hdc, &rect, borderBrush);
        DeleteObject(borderBrush);
    }

    UI_Container::Render(hdc);
}