#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	struct ThButtonState
	{
        ThButtonState()
            :
        m_TimeSinceStateChange(0.0f)
        {
            
        }
		ThFlags m_State;
		float m_TimeSinceStateChange;
	};

	struct ThMouse
	{
		ThButtonState m_Buttons[MouseButton::NumButtons];
		ThVec2f m_Pos;
		float m_Wheel;
	};

	struct ThInput
	{
        bool GetMouseButtonState(MouseButton btn, uint32_t state)
        {
            return m_Mouse.m_Buttons[btn].m_State.CheckFlag(state);
        }
        
        bool SetMouseButtonState(MouseButton btn, bool enable, uint32_t state)
        {
            bool oldState = GetMouseButtonState(btn, state);
            
            if (oldState != enable)
            {
                m_Mouse.m_Buttons[btn].m_State.SetFlag(enable, state);
                m_Mouse.m_Buttons[btn].m_State.m_TimeSinceStateChange = 0.0;
            }            
        }
        
        ThVec2f& GetMousePos()
        {
            return m_Mouse.m_Pos;
        }
        
		ThMouse m_Mouse;
	};
}
