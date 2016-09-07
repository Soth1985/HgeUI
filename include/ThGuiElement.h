#pragma once

#include "ThInput.h"
#include "ThDelegate.h"
#include <vector>

namespace Thor
{
	class ThGuiElement : std::enable_shared_from_this<ThGuiContext>
	{
	public:
		virtual ~ThGuiElement();
		virtual void Layout(const ThRectf& parentArea);
		virtual void ProcessInput();
		virtual void Render();

		typedef ThDelegate<ThGuiElementPtr, float, float> OnMouseMoveDel;
		typedef ThDelegate<ThGuiElementPtr, MouseButton> OnMouseButtonPressedDel;
		typedef ThDelegate<ThGuiElementPtr, MouseButton> OnMouseButtonReleasedDel;

		OnMouseMoveDel md_OnMouseMove;
		OnMouseButtonPressedDel md_OnMouseButtonPressed;
		OnMouseButtonReleasedDel md_OnMouseButtonReleased;
	protected:		
		typedef std::vector<ThGuiElementPtr> ChildrenContainer;

		ThGuiElementWeakPtr m_Parent;
		ThGuiContextWeakPtr m_Context;
		ChildrenContainer m_Children;
		uint32_t m_ID;
		std::string m_Name;
	};
}