#include "ThGuiContext.h"

using namespace Thor;

ThGuiContext::ThGuiContext()
    :
m_LastElementID(0)
{
    
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

void ThGuiContext::Update()
{
    UpdateInputImpl();
    m_Root->Layout(m_DrawArea);
    m_Root->ProcessInput();
}

void ThGuiContext::Render()
{
    m_Root->Render();
    RenderImpl();
}
