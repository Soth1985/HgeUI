#pragma once

#include "ThGuiForward.h"
#include "ThDelegate.h"

namespace Thor
{
    struct ThViewStateData
    {
        ThViewStateData();
        ThTexHandle m_Texture;
        ThColor m_Color;
        float m_BorderWidth;
        ThColor m_BorderColor;
    };
    
	class ThStatefulView
    {
    public:
        ThStatefulView();
        void SetStateData(WidgetViewState state, const ThViewStateData& data);
        const ThViewStateData& GetStateData(WidgetViewState state)const;
        
        typedef ThDelegate<> OnStateDataChangedDel;
        
        OnStateDataChangedDel md_OnStateDataChanged;
    private:
        ThViewStateData m_States[(int32_t)WidgetViewState::NumStates];
    };
}