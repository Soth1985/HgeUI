#pragma once

#include "ThVec2.h"
#include "ThRect.h"
#include "ThDim.h"
#include "ThColor.h"
#include <stdint.h>
#include <memory>

namespace Thor
{
	typedef ThVec2<float> ThVec2f;
	typedef ThVec2<ThDim> ThDim2;
	typedef ThRect<ThVec2f> ThRectf;
	typedef ThRect<ThDim2> ThDimRect;
	typedef uint32_t ThTexHandle;
	typedef uint32_t ThElementID;

	class ThGuiContext;
	typedef std::shared_ptr<ThGuiContext> ThGuiContextPtr;
	typedef std::weak_ptr<ThGuiContext> ThGuiContextWeakPtr;
	class ThGuiElement;
	typedef std::shared_ptr<ThGuiElement> ThGuiElementPtr;
	typedef std::weak_ptr<ThGuiElement> ThGuiElementWeakPtr;
	class ThGuiButton;
	class ThGuiImage;
	class ThGuiPanel;

	enum class Anchor : uint32_t
	{		
		TopLeft,
		Top,
		TopRight,
		Left,
		Center,
		Right,
		BottomLeft,
		Bottom,
		BottomRight,
		NumAnchors
	};

	enum class MouseButton : uint32_t
	{
		Left,
		Middle,
		Right,
		NumButtons
	};

	enum class InputButtonState : uint32_t
	{
		Down = 1<<0,
		JustPressed = 1<<1,
		JustReleased = 1<<2
	};

	enum class WidgetType : uint32_t
	{
		Button,
		Image,
		Panel
	};

	enum class WidgetFlag : uint32_t
	{
		FillParent = 1 << 0
	};
}
