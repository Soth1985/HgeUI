#include "ThGuiText.h"
#include "ThGuiContext.h"

using namespace Thor;

ThGuiText::ThGuiText(ThGuiContext* context)
    :
ThGuiElement(context),
m_TextColor(0, 0, 0, 255),
m_TextScale(1.0),
m_VertTextAlignment(TextVertAlignment::Top),
m_HorTextAlignment(TextHorAlignment::Left)
{
	m_Font = context->GetDefaultFont();
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

TextVertAlignment ThGuiText::GetVertTextAlignment()const
{
	return m_VertTextAlignment;
}

void ThGuiText::SetVertTextAlignment(TextVertAlignment align)
{
	m_VertTextAlignment = align;
}

TextHorAlignment ThGuiText::GetHorTextAlignment()const
{
	return m_HorTextAlignment;
}

void ThGuiText::SetHorTextAlignment(TextHorAlignment align)
{
	m_HorTextAlignment = align;
}

void ThGuiText::RenderElement(ThCommandBuffer& cmd, uint16_t depth)
{
    ThGuiElement::RenderElement(cmd, depth);

	if (m_Font && !m_Text.empty())
	{
		ThLayer layer(m_Layer, depth);
		ThVec2f textPos = m_RealRect.TopLeft();

		if (m_VertTextAlignment == TextVertAlignment::Center)
		{
			float textHeight = m_Context->GetFontHeight(m_Font) * m_TextScale;
			textPos = textPos + ThVec2f(0.0, 0.5 * (m_RealRect.Height() - textHeight));
		}
		else if (m_VertTextAlignment == TextVertAlignment::Bottom)
		{
			float textHeight = m_Context->GetFontHeight(m_Font) * m_TextScale;
			textPos = textPos + ThVec2f(0.0, m_RealRect.Height() - textHeight);
		}

		if (m_HorTextAlignment == TextHorAlignment::Center)
		{
			float textWidth = m_Context->GetStringWidth(m_Font, m_Text) * m_TextScale;
			textPos = textPos + ThVec2f(0.5 * (m_RealRect.Width() - textWidth), 0.0);
		}
		else if (m_HorTextAlignment == TextHorAlignment::Right)
		{
			float textWidth = m_Context->GetStringWidth(m_Font, m_Text) * m_TextScale;
			textPos = textPos + ThVec2f(m_RealRect.Width() - textWidth, 0.0);
		}

		cmd.AddText(m_Text.c_str(), textPos, m_Font, m_TextScale, layer, m_TextColor);
	}    
}

bool ThGuiText::IsClipper()
{
    if (m_Font && !m_Text.empty())
        return true;
    
    return ThGuiElement::IsClipper();
}