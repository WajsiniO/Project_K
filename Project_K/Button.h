#pragma once
#include "UI_Components.h"
#include "UI_Style.h"
#include <string>
#include <functional>

class Button : public UI_Components {
public:
    Button(int x, int y, int width, int height, const wchar_t* text, UI_Components* parent = nullptr);
    virtual ~Button() override;

    void SetText(const wchar_t* text) { m_text = (text != nullptr ? text : L""); }

    void SetStyle(const ButtonStyle& style) { m_style = style; }

    void SetOnClick(std::function<void()> onClick) { m_onClick = onClick; }

    virtual void Update(int mouseX, int mouseY, bool isMouseDown) override;
    virtual void Render(HDC hdc) override;

private:
    std::wstring m_text;
    ButtonStyle m_style;
    std::function<void()> m_onClick;
    bool m_wasPressed;
};