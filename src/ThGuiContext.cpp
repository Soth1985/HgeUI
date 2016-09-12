#include "ThGuiContext.h"
#include "ThGuiElement.h"

using namespace Thor;

ThGuiContext::ThGuiContext()
    :
m_LastElementID(1),
m_DeltaTime(0.0),
m_PixelScale(1.0),
m_InvPixelScale(1.0)
{
	m_Root = std::make_shared<ThGuiElement>(this);
}

ThGuiContext::~ThGuiContext()
{
    
}

ThElementID ThGuiContext::GenElementID()
{
    return m_LastElementID++;
}

void ThGuiContext::SetDrawArea(const ThRectf& area)
{
    m_DrawArea = area;
}

const ThRectf& ThGuiContext::GetDrawArea()const
{
    return m_DrawArea;
}

ThGuiElementPtr ThGuiContext::GetRootElement()
{
    return m_Root;
}

const ThInput& ThGuiContext::GetInput()const
{
    return m_Input;
}

float ThGuiContext::GetDeltaTime()const
{
	return m_DeltaTime;
}

void ThGuiContext::Update()
{
    m_ActiveElement = nullptr;
    m_HotElement = nullptr;
    UpdateInputImpl();
    m_Root->LayoutElementRecursive(m_DrawArea);
    
    if (m_ActiveElement)
    {
		for (int32_t btn = 0; btn < (int32_t)MouseButton::NumButtons; ++btn)
		{
			if (m_Input.GetMouseButtonState((MouseButton)btn, (int32_t)InputButtonState::JustPressed))
				m_ActiveElement->md_OnMouseButtonPressed.Invoke(m_ActiveElement.get(), (MouseButton)btn);					
		}
    }
	else if (m_LastActiveElement)
	{
		for (int32_t btn = 0; btn < (int32_t)MouseButton::NumButtons; ++btn)
		{
			if (m_Input.GetMouseButtonState((MouseButton)btn, (int32_t)InputButtonState::JustReleased))
				m_LastActiveElement->md_OnMouseButtonReleased.Invoke(m_ActiveElement.get(), (MouseButton)btn);
		}
	}
    
    if (m_HotElement != m_LastHotElement)
    {
        ThVec2f mousePos = m_Input.GetMousePos();
        
        if (m_HotElement)
            m_HotElement->md_OnMouseEnter.Invoke(m_HotElement.get(), mousePos);
        
        if (m_LastHotElement)
            m_LastHotElement->md_OnMouseLeave.Invoke(m_LastHotElement.get(), mousePos);
            
    }
    else if (m_HotElement)
    {
        ThVec2f mousePos = m_Input.GetMousePos();
        m_HotElement->md_OnMouseMove.Invoke(m_HotElement.get(), mousePos);
    }
    
    m_LastHotElement = m_HotElement;
    m_LastActiveElement = m_ActiveElement;
}

void ThGuiContext::Render()
{
	m_RenderBuf.Reset();
    m_Root->RenderRecursive(m_RenderBuf, 0);
    RenderImpl();
}

ThGuiElementPtr ThGuiContext::GetHotElement()
{
	return m_HotElement;
}

void ThGuiContext::SetHotElement(ThGuiElementPtr elem)
{    
    m_HotElement = elem;
}

ThGuiElementPtr ThGuiContext::GetActiveElement()
{
	return m_ActiveElement;
}

void ThGuiContext::SetActiveElement(ThGuiElementPtr elem)
{
    if (m_HotElement == elem)
        m_ActiveElement = elem;
}

ThFontHandle ThGuiContext::GetDefaultFont()const
{
	return m_DefaultFont;
}

void ThGuiContext::SetDefaultFont(ThFontHandle font)
{
	m_DefaultFont = font;
}

float ThGuiContext::GetPixelScale()const
{
    return m_PixelScale;
}

float ThGuiContext::GetInvPixelScale()const
{
    return m_InvPixelScale;
}

void ThGuiContext::SetPixelScale(float scale)
{
    m_PixelScale = scale;
    m_InvPixelScale = 1.0f / scale;
}