#pragma once

#include "ThGuiElement.h"

namespace Thor
{
    class ThGuiText : public ThGuiElement
    {
    public:
        ThGuiText(ThGuiContext* context);
        ThFontHandle GetFont()const;
        void SetFont(ThFontHandle font);
        const ThColor& GetTextColor()const;
        void SetTextColor(const ThColor& color);
        float GetTextScale()const;
        void SetTextScale(float scale);
        const std::string& GetText()const;
        void SetText(const std::string& text);
    protected:
        virtual void RenderElement(ThCommandBuffer& cmd, uint16_t depth);
        
        ThFontHandle m_Font;
        ThColor m_TextColor;
        float m_TextScale;
        std::string m_Text;
    };
}