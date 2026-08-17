#include "UI_Components.h"

UI_Components::UI_Components(int x, int y, int width, int height, UI_Components* parent)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_isVisible(true), m_state(UIState::Normal), m_parent(parent) {
}

UI_Components::~UI_Components() {
}

int UI_Components::GetGlobalX() const {
    if (m_parent != nullptr) {
        return m_parent->GetGlobalX() + m_x;
    }
    return m_x;
}

int UI_Components::GetGlobalY() const {
    if (m_parent != nullptr) {
        return m_parent->GetGlobalY() + m_y;
    }
    return m_y;
}

bool UI_Components::IsPointInside(int screenX, int screenY) const {
    int gx = GetGlobalX();
    int gy = GetGlobalY();
    return (screenX >= gx && screenX <= gx + m_width &&
            screenY >= gy && screenY <= gy + m_height);
}

void UI_Components::Update(int mouseX, int mouseY, bool isMouseDown) {
    if (!m_isVisible) return;

    if (IsPointInside(mouseX, mouseY)) {
        m_state = isMouseDown ? UIState::Pressed : UIState::Hovered;
    } else {
        m_state = UIState::Normal;
    }
}

void UI_Components::Render(HDC hdc) {
    // Klasa bazowa - pusta implementacja
}