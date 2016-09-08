#pragma once

#include "ThGuiElement.h"
#include "ThGuiContext.h"

using namespace Thor;

ThGuiElement::ThGuiElement(ThGuiContext* context)
    :
m_Parent(nullptr),
m_Context(context),
m_LayoutRect(ThDim2(ThDim(0.0, 0), ThDim(0.0, 0)), ThDim2(ThDim(1.0, 0), ThDim(1.0, 0))),
m_Color(128, 128, 128, 255),
m_Texture(0)
{
    m_ID = m_Context->GenerateElementID();
}

ThGuiElement::~ThGuiElement()
{
    
}

void ThGuiElement::Layout(const ThRectf& parentArea)
{
    
}

void ThGuiElement::ProcessInput()
{
    
}

void ThGuiElement::Render()
{
    
}

bool ThGuiElement::PushChild(ThGuiElementPtr child)
{
    int32_t index = GetChildIndex(child->GetElementID());
    
    if (index < 0)
        return false;
    
    m_Children.push_back(child);
    child->SetParent(this);
    return true;
}

ThGuiElementPtr ThGuiElement::GetChild(ThElementID child)
{
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        if (m_Children[i]->GetElementID() == child->GetElementID())
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
        m_Children[i]->GetGetChildrenByNameRecursive(name, children);
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

void ThGuiElement::IsStateSet(uint32_t state)
{
    return m_State.CheckFlag(state);
}

void ThGuiElement::SetState(bool enable, uint32_t state)
{
    m_State.SetFlag(enable, state);
}

void ThGuiElement::SetStateRecursive(bool enable, uint32_t state)
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

void ThGuiElement::SetColor(ThColor& color)
{
    m_Color = color;
}

ThTexHandle ThGuiElement::GetTexture()const
{
    return m_Texture;
}

void ThGuiElement::SetTexture(ThTexHandle texture)
{
    m_Texture = texture;
}