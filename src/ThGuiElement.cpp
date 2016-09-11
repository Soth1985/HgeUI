#pragma once

#include "ThGuiElement.h"
#include "ThGuiContext.h"
#include "ThGuiUtil.h"

using namespace Thor;

ThGuiElement::ThGuiElement(ThGuiContext* context)
    :
m_Parent(nullptr),
m_Context(context),
m_LayoutRect(Util::MakeDimRect(0.0, 0, 0.0, 0, 1.0, 0, 1.0, 0)),
//m_Color(128, 128, 128, 255),
m_Texture(0),
m_Layer((uint16_t)WidgetLayer::Normal),
m_BorderWidth(0.0)
{
    m_ID = m_Context->GenElementID();
}

ThGuiElement::~ThGuiElement()
{
    
}

void ThGuiElement::LayoutElementRecursive(const ThRectf& parentArea)
{
    SetState(false, (int32_t)WidgetState::Clipped);

	if (IsStateSet((int32_t)WidgetState::Invisible))
		return;

    ThVec2f parentSize = parentArea.Size();
    ThDim2 relPos = GetPosition();
    ThDim2 relSize = GetSize();
    ThVec2f absPos = parentArea.TopLeft() + Util::GetAbsoluteDimension(relPos, parentSize);
    ThVec2f absSize = Util::GetAbsoluteDimension(relSize, parentSize);

	if (absSize.X() < 0.0)
		absSize.X() = 0.0;

	if (absSize.Y() < 0.0)
		absSize.Y() = 0.0;

    m_RealRect.TopLeft() = absPos;
    m_RealRect.BottomRight() = absPos + absSize;
    
	if ((m_RealRect.Area() == 0.0) || !parentArea.Intersects(m_RealRect))
	{
		SetState(true, (int32_t)WidgetState::Clipped);
		return;
	}    
	
    //TODO anchor solver
	LayoutElement(parentArea);
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->LayoutElementRecursive(m_RealRect);
    }
    ProcessInput();
}

void ThGuiElement::LayoutElement(const ThRectf& parentArea)
{

}

void ThGuiElement::ProcessInput()
{
	int32_t inputFlags = (int32_t)WidgetState::Clipped | (int32_t)WidgetState::Invisible | (int32_t)WidgetState::Inactive;
    
	if (IsStateSet(inputFlags))
        return;
    
    /*for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->ProcessInputRecursive();
    }*/
    
    bool isMouseInside = m_RealRect.IsInside(m_Context->GetInput().GetMousePos());
    bool isMouseBtnPressed = false;
    
    for (uint32_t btn = 0; btn < MouseButton::NumButtons; ++btn)
        isMouseBtnPressed |= m_Context->GetInput().GetMouseButtonState(btn, (int32_t)InputButtonState::Down);

    if (m_Context->GetHotElement() == nullptr)
    {
        if (isMouseInside)
        {
            m_Context->SetHotElement(This());
        }
    }
    
    if (m_Context->GetActiveElement() == nullptr)
	{
		if (isMouseInside && isMouseBtnPressed)
		{
			m_Context->SetActiveElement(This());
		}
	}
}

void ThGuiElement::RenderElement(ThCommandBuffer& cmd, uint16_t depth)
{
    ThLayer layer(m_Layer, depth);
    
    if (m_Color.m_A > 0)
        cmd.AddQuad(m_RealRect, m_Texture, layer, m_Color);
        
    if (m_BorderWidth > 0 && m_BorderColor.m_A > 0)
    {
        ThVec2f rectPoints[4];
        Util::DecomposeRect(m_RealRect, rectPoints);
		
		float borderWidth = m_BorderWidth * m_Context->GetInvPixelScale();
		ThVec2f offsets[4] = 
		{
			{0.0, borderWidth},
			{0.0, 0.0},
			{0.0, 0.0},
			{borderWidth, 0.0}
		};
        
        cmd.AddLine(rectPoints[0] + offsets[0], rectPoints[1] + offsets[0], m_BorderWidth, layer, m_BorderColor);
        cmd.AddLine(rectPoints[1] + offsets[1], rectPoints[2] + offsets[1], m_BorderWidth, layer, m_BorderColor);
        cmd.AddLine(rectPoints[2] + offsets[2], rectPoints[3] + offsets[2], m_BorderWidth, layer, m_BorderColor);
        cmd.AddLine(rectPoints[3] + offsets[3], rectPoints[0] + offsets[3], m_BorderWidth, layer, m_BorderColor);
    }
}

void ThGuiElement::RenderRecursive(ThCommandBuffer& cmd, uint16_t depth)
{
	int32_t visibilityFlags = (int32_t)WidgetState::Clipped | (int32_t)WidgetState::Invisible;
    if (IsStateSet(visibilityFlags))
        return;
    
    //if (GetNumChildren() > 0)
    {
        cmd.PushState(m_RealRect);
    }
    
    RenderElement(cmd, depth);
    
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->RenderRecursive(cmd, depth + 1);
    }
    
    //if (GetNumChildren() > 0)
    {
        cmd.PopState();
    }
}

WidgetType ThGuiElement::GetType()const
{
    return WidgetType::Panel;
}

bool ThGuiElement::PushChild(ThGuiElementPtr child)
{
    int32_t index = GetChildIndex(child->GetElementID());
    
    if (index >= 0)
        return false;
    
    m_Children.push_back(child);
    child->SetParent(this);
    return true;
}

ThGuiElementPtr ThGuiElement::GetChild(ThElementID child)
{
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        if (m_Children[i]->GetElementID() == child)
            return m_Children[i];
    }
    
    return nullptr;
}

ThGuiElementPtr ThGuiElement::GetChildRecursive(ThElementID child)
{
    ThGuiElementPtr result = GetChild(child);
    
    if (result)
        return result;
    
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        result = m_Children[i]->GetChildRecursive(child);
        
        if (result)
            return result;
    }
    
    return nullptr;
}

size_t ThGuiElement::GetNumChildren()const
{
    return m_Children.size();
}

ThGuiElementPtr ThGuiElement::GetChildByIndex(size_t index)
{
    return m_Children[index];
}

ThGuiElementPtr ThGuiElement::GetChildByName(const std::string& name)
{
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        if (m_Children[i]->GetName() == name)
            return m_Children[i];
    }
    
    return nullptr;
}

ThGuiElementPtr ThGuiElement::GetChildByNameRecursive(const std::string& name)
{
    ThGuiElementPtr result = GetChildByName(name);
    
    if (result)
        return result;
    
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        result = m_Children[i]->GetChildByNameRecursive(name);
        if (result)
            return result;
    }
    
    return nullptr;
}

void ThGuiElement::GetChildrenByName(const std::string& name, ChildrenContainer& children)
{
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        if (m_Children[i]->GetName() == name)
            children.push_back(m_Children[i]);
    }
}

void ThGuiElement::GetChildrenByNameRecursive(const std::string& name, ChildrenContainer& children)
{
    GetChildrenByName(name, children);
    
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->GetChildrenByNameRecursive(name, children);
    }
}

bool ThGuiElement::SwapChilds(ThElementID c1, ThElementID c2)
{
    int32_t c1Index = GetChildIndex(c1);
    int32_t c2Index = GetChildIndex(c2);
    
    if (c1Index < 0)
        return false;
    
    if (c2Index < 0)
        return false;
    
    std::swap(m_Children[c1Index], m_Children[c2Index]);
    return true;
}

int32_t ThGuiElement::GetChildIndex(ThElementID c)const
{
    for (int32_t i = 0; i < m_Children.size(); ++i)
    {
        if (m_Children[i]->GetElementID() == c)
            return i;
    }
    
    return -1;
}

ThGuiElement* ThGuiElement::GetParent()
{
    return m_Parent;
}

void ThGuiElement::SetParent(ThGuiElement* element)
{
    m_Parent = element;
}

ThGuiElementPtr ThGuiElement::This()
{
    return shared_from_this();
}

ThElementID ThGuiElement::GetElementID()const
{
    return m_ID;
}

const std::string& ThGuiElement::GetName()const
{
    return m_Name;
}

void ThGuiElement::SetName(const std::string& name)
{
    m_Name = name;
}

bool ThGuiElement::IsStateSet(int32_t state)
{
    return m_State.CheckFlags(state);
}

void ThGuiElement::SetState(bool enable, int32_t state)
{
    m_State.SetFlag(enable, state);
}

void ThGuiElement::SetStateRecursive(bool enable, int32_t state)
{
    m_State.SetFlag(enable, state);
    
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->SetStateRecursive(enable, state);
    }
}

const ThDim2& ThGuiElement::GetPosition()const
{
    return m_LayoutRect.TopLeft();
}

void ThGuiElement::SetPosition(const ThDim2& pos)
{
    ThDim2 offset = pos - GetPosition();
    m_LayoutRect.TopLeft() = pos;
    m_LayoutRect.BottomRight() = m_LayoutRect.BottomRight() + offset;
}

ThDim2 ThGuiElement::GetSize()const
{
    return m_LayoutRect.BottomRight() - m_LayoutRect.TopLeft();
}

void ThGuiElement::SetSize(const ThDim2& pos)
{
    m_LayoutRect.BottomRight() = m_LayoutRect.TopLeft() + pos;
}

const ThColor& ThGuiElement::GetColor()const
{
    return m_Color;
}

void ThGuiElement::SetColor(const ThColor& color)
{
    m_Color = color;
}

ThTexHandle ThGuiElement::GetTexture()const
{
    return m_Texture;
}

void ThGuiElement::SetTexture(ThTexHandle texture, const ThColor& overrideColor)
{
    m_Texture = texture;

	SetColor(overrideColor);
}

const ThColor& ThGuiElement::GetBorderColor()const
{
	return m_BorderColor;
}

void ThGuiElement::SetBorderColor(const ThColor& color)
{
	m_BorderColor = color;
}

float ThGuiElement::GetBorderWidth()const
{
	return m_BorderWidth;
}

void ThGuiElement::SetBorderWidth(float width)
{
	m_BorderWidth = width;
}

uint16_t ThGuiElement::GetLayer()const
{
	return m_Layer;
}

void ThGuiElement::SetLayer(uint16_t layer)
{
	m_Layer = layer;
}

void ThGuiElement::SetLayerRecursive(uint16_t layer)
{
    SetLayer(layer);
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->SetLayerRecursive(layer);
    }
}