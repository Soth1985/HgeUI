#include "ThGuiContext.h"
#include "ThGuiElement.h"

using namespace Thor;

ThGuiContext::ThGuiContext()
    :
m_LastElementID(0),
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
    //m_Root->ProcessInputRecursive();
    
    bool hasPresedButtons = false;
    bool hasReleasedButtons = false;
    
    for (uint32_t btn = 0; btn < MouseButton::NumButtons; ++btn)
    {
        hasPressedButtons |= m_Input.GetMouseButtonState(btn, (int32_t)InputButtonState::JustPressed);
        hasReleasedButtons |= m_Input.GetMouseButtonState(btn, (int32_t)InputButtonState::JustReleased);
    }
    
    if (m_ActiveElement != nullptr)
    {
        if (hasPressedButtons)
        {
            m_ActiveElement->md_OnMouseButtonPressed.Invoke(m_ActiveElement.get(), m_Input.m_Mouse);
        }
        
        if (hasReleasedButtons)
        {
            m_ActiveElement->md_OnMouseButtonRelease.Invoke(m_ActiveElement.get(), m_Input.m_Mouse);
        }
    }
    
    if (m_HotElement != m_LastHotElement)
    {
        ThVec2f mousePos = m_Input.GetMousePos();
        
        if (m_HotElement)
            m_HotElement->md_OnMouseEnter.Invoke(m_HotElement.get(), mousePos.X(), mousePos.Y());
        
        if (m_LastHotElement)
            m_LastHotElement->md_OnMouseLeave.Invoke(m_HotElement.get(), mousePos.X(), mousePos.Y());
            
    }
    else if (m_HotElement)
    {
        ThVec2f mousePos = m_Input.GetMousePos();
        m_HotElement->md_OnMouseMove.Invoke(m_HotElement.get(), mousePos.X(), mousePos.Y());
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
    m_InvPixelScale = 1.0 / scale;
}