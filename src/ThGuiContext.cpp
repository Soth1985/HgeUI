#include "ThGuiContext.h"
#include "ThGuiElement.h"

using namespace Thor;

ThGuiContext::ThGuiContext()
    :
m_LastElementID(0),
m_DeltaTime(0.0)
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
    UpdateInputImpl();
    m_Root->LayoutRecursive(m_DrawArea);
	m_ActiveElement = nullptr;
	m_HotElement = nullptr;
    m_Root->ProcessInputRecursive();
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
	m_ActiveElement = elem;
}
