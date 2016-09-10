#include "ThStatefulView.h"

using namespace Thor;

ThViewStateData::ThViewStateData()
    :
m_Texture(0),
m_BorderWidth(0.0)
{
    
}

ThStatefulView::ThStatefulView()
{
    
}

void ThStatefulView::SetStateData(WidgetViewState state, const ThViewStateData& data)
{
    if (state == WidgetViewState::NumStates)
    {
        for (int32_t i = 0; i < (int32_t)WidgetViewState::NumStates; ++i)
        {
            m_States[i] = data;
        }
    }
    else
    {
        m_States[(int32_t)state] = data;
    }
    
    md_OnStateDataChanged.Invoke();
}

const ThViewStateData& ThStatefulView::GetStateData(WidgetViewState state)const
{
    return m_States[(int32_t)state];
}