#include "ThGuiText.h"

using namespace Thor;

ThGuiText::ThGuiText(ThGuiContext* context)
    :
ThGuiElement(context),
m_Font(0),
m_TextColor(0, 0, 0, 255),
m_TextScale(0)
{
    
}

ThFontHandle ThGuiText::GetFont()const
{
    return m_Font;
}

void ThGuiText::SetFont(ThFontHandle font)
{
    m_Font = font;
}

const ThColor& ThGuiText::GetTextColor()const
{
    return m_TextColor;
}

void ThGuiText::SetTextColor(const ThColor& color)
{
    m_TextColor = color;
}

float ThGuiText::GetTextScale()const
{
    return m_TextScale;
}

void ThGuiText::SetTextScale(float scale)
{
    m_TextScale = scale;
}

const std::string& ThGuiText::GetText()const
{
    return m_Text;
}

void ThGuiText::SetText(const std::string& text)
{
    m_Text = text;
}

void ThGuiText::RenderElement(ThCommandBuffer& cmd, uint16_t depth)
{
    ThGuiElement::RenderElement(cmd, depth);
    ThLayer layer(m_Layer, depth);
    cmd.AddText(m_Text.c_str(), m_RealRect.TopLeft(), m_Font, m_TextScale);
}