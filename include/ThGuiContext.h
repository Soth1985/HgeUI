#pragma once

#include "ThGuiForward.h"
#include "ThInput.h"

namespace Thor
{
	class ThGuiContext : std::enable_shared_from_this<ThGuiContext>
	{
	public:
		virtual ~ThGuiContext();
		int32_t GenElementID();
		virtual ThTexHandle CreateTexture();
	private:
		ThInput m_Input;
		ThRectf m_DrawArea;
		ThGuiElementPtr m_Root;
		int32_t m_LastID;
	protected:
		virtual void UpdateInputImpl() = 0;
		virtual void RenderImpl() = 0;
	};
}