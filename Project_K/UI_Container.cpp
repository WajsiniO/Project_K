#include "UI_Container.h"

UI_Container::UI_Container(int x, int y, int width, int height, UI_Components* parent)
    : UI_Components(x, y, width, height, parent) {
}

UI_Container::~UI_Container() {
    ClearChildren();
}

void UI_Container::AddChild(UI_Components* child) {
    if (child != nullptr) {
        child->SetParent(this);
        m_children.push_back(child);
    }
}

void UI_Container::RemoveChild(UI_Components* child) {
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (*it == child) {
            delete *it;
            m_children.erase(it);
            break;
        }
    }
}

void UI_Container::ClearChildren() {
    for (UI_Components* child : m_children) {
        delete child;
    }
    m_children.clear();
}

void UI_Container::Update(int mouseX, int mouseY, bool isMouseDown) {
    if (!m_isVisible) return;

    UI_Components::Update(mouseX, mouseY, isMouseDown);

    for (UI_Components* child : m_children) {
        if (child != nullptr && child->IsVisible()) {
            child->Update(mouseX, mouseY, isMouseDown);
        }
    }
}

void UI_Container::Render(HDC hdc) {
    if (!m_isVisible) return;

    for (UI_Components* child : m_children) {
        if (child != nullptr && child->IsVisible()) {
            child->Render(hdc);
        }
    }
}