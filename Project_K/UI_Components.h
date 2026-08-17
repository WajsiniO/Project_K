#pragma once
#include <windows.h>
#include "UI_Style.h"

class UI_Components {
public:
    UI_Components(int x, int y, int width, int height, UI_Components* parent = nullptr);
    virtual ~UI_Components();

    virtual void Update(int mouseX, int mouseY, bool isMouseDown);
    virtual void Render(HDC hdc);

    int GetLocalX() const { return m_x; }
    int GetLocalY() const { return m_y; }
    void SetPosition(int x, int y) { m_x = x; m_y = y; }

    int GetGlobalX() const;
    int GetGlobalY() const;

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    void SetSize(int width, int height) { m_width = width; m_height = height; }

    bool IsVisible() const { return m_isVisible; }
    void SetVisible(bool visible) { m_isVisible = visible; }

    UIState GetState() const { return m_state; }
    void SetState(UIState state) { m_state = state; }

    bool IsPointInside(int screenX, int screenY) const;

    UI_Components* GetParent() const { return m_parent; }
    void SetParent(UI_Components* parent) { m_parent = parent; }

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    bool m_isVisible;

    UIState m_state;
    UI_Components* m_parent;
};