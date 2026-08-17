#pragma once
#include "UI_Container.h"
#include "UI_Style.h"
#include "Button.h"
#include <functional>

class MenuPanel : public UI_Container {
public:
    MenuPanel(int x, int y, int width, int height, const MenuStyle& style, UI_Components* parent = nullptr);
    virtual ~MenuPanel() override;

    Button* AddButton(int x, int y, int width, int height, const wchar_t* text, std::function<void()> onClick = nullptr);

    void SetMenuStyle(const MenuStyle& style);
    const MenuStyle& GetMenuStyle() const { return m_menuStyle; }

    virtual void Render(HDC hdc) override;

private:
    MenuStyle m_menuStyle;
};