#include "ThGuiButton.h"
#include "ThGuiText.h"

using namespace Thor

ThGuiButton::ThGuiButton(ThGuiContext* context)
    :
m_CurState(WidgetViewState::NumStates)
{
    m_Caption = std::make_shared<ThGuiButton>(context);
    m_Caption->SetVertTextAlignment(VertTextAlignment::Center);
    m_Caption->SetHorTextAlignment(HorTextAlignment::Center);
    PushChild(m_Caption);
    
    mdc_OnStateDataChanged = m_States.md_OnStateDataChanged.Connect([this]void()
                                                                    {
                                                                        this->ApplyState(m_CurState);
                                                                    });
    mdc_OnMouseEnter = md_OnMouseEnter.Connect([this]void()
                                               {
                                                   this->ApplyState(WidgetViewState::MouseOver);
                                               });
    mdc_OnMouseLeave = md_OnMouseLeave.Connect([this]void()
                                               {
                                                   this->ApplyState(WidgetViewState::Default);
                                               });
    mdc_OnMouseButtonPressed = md_OnMouseButtonPressed.Connect([this]void()
                                                      {
                                                          this->ApplyState(WidgetViewState::Pressed);
                                                      });
    mdc_OnMouseButtonReleased= md_OnMouseButtonReleased.Connect([this]void()
                                                       {
                                                           this->ApplyState(WidgetViewState::Default);
                                                       });
}

void ThGuiButton::ApplyState(WidgetViewState state)
{
    //if (state != m_CurState)
    {
        m_CurState = state;
        const ThViewStateData& data = m_States.GetStateData(state);
        SetTexture(data.m_Texture);
        SetColor(data.m_Color);
        SetBorderWidth(data.m_BorderWidth);
        SetBorderColor(data.m_BorderColor);
    }
}

void ThGuiButton::RenderElement(ThCommandBuffer& cmd, uint16_t depth)
{
    if (m_CurState == WidgetViewState::NumStates)
        ApplyState(WidgetViewState::Default);
    
    ThGuiElement::RenderElement(cmd, depth);
}

ThStatefulView& ThGuiButton::GetStates()
{
    return m_States;
}

ThGuiTextPtr ThGuiButton::GetCaption()
{
    return m_Caption;
}