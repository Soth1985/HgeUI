#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	struct ThButtonState
	{
		uint32_t m_State;
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
		ThMouse m_Mouse;
	};
}
