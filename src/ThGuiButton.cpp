#include "ThGuiButton.h"
#include "ThGuiText.h"

using namespace Thor;

ThGuiButton::ThGuiButton(ThGuiContext* context)
    :
ThGuiElement(context),
m_CurState(WidgetViewState::NumStates)
{
    m_Caption = std::make_shared<ThGuiText>(context);
    m_Caption->SetVertTextAlignment(TextVertAlignment::Center);
    m_Caption->SetHorTextAlignment(TextHorAlignment::Center);
	m_Caption->SetState(true, (int32_t)WidgetState::Inactive);
    PushChild(m_Caption);
    
    mdc_OnStateDataChanged = m_States.md_OnStateDataChanged.Connect([this]()
	{
		this->ApplyState(m_CurState);
	});

    mdc_OnMouseEnter = md_OnMouseEnter.Connect([this](ThGuiElement*, const ThVec2f&)
	{
		this->ApplyState(WidgetViewState::MouseOver);
	});

    mdc_OnMouseLeave = md_OnMouseLeave.Connect([this](ThGuiElement*, const ThVec2f&)
	{
		this->ApplyState(WidgetViewState::Default);
	});

    mdc_OnMouseButtonPressed = md_OnMouseButtonPressed.Connect([this](ThGuiElement*, MouseButton btn)
	{
		if (btn == MouseButton::Left)
			this->ApplyState(WidgetViewState::Pressed);
	});

    mdc_OnMouseButtonReleased = md_OnMouseButtonReleased.Connect([this](ThGuiElement*, MouseButton btn)
	{
		if (btn == MouseButton::Left)
			this->ApplyState(WidgetViewState::Default);
	});
}

void ThGuiButton::ApplyState(WidgetViewState state)
{
    if (state != WidgetViewState::NumStates)
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