#include "ThStatefulView.h"

using namespace Thor;

ThViewStateData::ThViewStateData()
    :
m_Texture(0),
m_BorderWidth(0.0),
m_Owner(nullptr)
{
    
}

ThStatefulView::ThStatefulView()
    :
m_CurState(WidgetState::NumStates)
{
    
}

void ThStatefulView::SetStateData(WidgetViewState state, const ThViewStateData& data)
{
    if (state == WidgetViewState::NumStates)
    {
        for (int32_t i = 0; i < WidgetViewState::NumStates; ++i)
        {
            m_States[i] = data;
        }
    }
    else
    {
        m_States[state] = data;
    }
    
    if (m_CurState != WidgetState::NumStates)
        md_OnStateDataChanged.Invoke();
}

void ThStatefulView::SwitchState(WidgetViewState targetState)
{
    m_CurState = targetState;
}

const ThViewStateData& ThStatefulView::GetStateData(WidgetViewState state)const
{
    return m_States[state];
}

const ThViewStateData& ThStatefulView::GetCurrentStateData()const
{
    return m_States[m_CurState];
}