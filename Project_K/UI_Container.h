#pragma once
#include "UI_Components.h"
#include <vector>

class UI_Container : public UI_Components {
public:
    UI_Container(int x, int y, int width, int height, UI_Components* parent = nullptr);
    virtual ~UI_Container() override;

    void AddChild(UI_Components* child);
    void RemoveChild(UI_Components* child);
    void ClearChildren();

    const std::vector<UI_Components*>& GetChildren() const { return m_children; }

    virtual void Update(int mouseX, int mouseY, bool isMouseDown) override;
    virtual void Render(HDC hdc) override;

protected:
    std::vector<UI_Components*> m_children;
};