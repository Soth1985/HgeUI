#pragma once

#include "ThGuiElement.h"
#include "ThStatefulView.h"

namespace Thor
{
	class ThGuiButton : public ThGuiElement
	{
	public:
        ThGuiButton(ThGuiContext* context);
		~ThGuiButton();
        ThStatefulView& GetStates();
        ThGuiTextPtr GetCaption();
        
	protected:
        void ApplyState(WidgetViewState state);
        virtual void RenderElement(ThCommandBuffer& cmd, uint16_t depth)override;
        
        ThGuiTextPtr m_Caption;
        ThStatefulView m_States;
        WidgetViewState m_CurState;
        ThDelegateConnection mdc_OnStateDataChanged;
        ThDelegateConnection mdc_OnMouseEnter;
        ThDelegateConnection mdc_OnMouseLeave;
        ThDelegateConnection mdc_OnMouseButtonPressed;
        ThDelegateConnection mdc_OnMouseButtonReleased;
	};
}