#pragma once

#include "ThVec2.h"
#include "ThRect.h"
#include "ThDim.h"
#include "ThColor.h"
#include "ThFlags.h"
#include "ThRange.h"
#include "ThLayer.h"
#include <stdint.h>
#include <memory>

namespace Thor
{
	typedef ThVec2<float> ThVec2f;
	typedef ThVec2<ThDim> ThDim2;
	typedef ThRect<ThVec2f> ThRectf;
	typedef ThRect<ThDim2> ThDimRect;
    typedef ThFlags<uint32_t> ThFlags32;
	typedef uint32_t ThTexHandle;
    typedef uint32_t ThFontHandle;
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

	enum class Anchor : int32_t
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

	enum class MouseButton : int32_t
	{
		Left,
		Middle,
		Right,
		NumButtons
	};

	enum class InputButtonState : int32_t
	{
		Down = 1<<0,
		JustPressed = 1<<1,
		JustReleased = 1<<2
	};

	enum class WidgetType : int32_t
	{
		Button,
		Image,
		Panel,
        Text
	};

	enum class WidgetState : int32_t
	{
		LayoutRequired = 1 << 0,
        ProcessInput = 1 << 1,
        RenderWidget = 1 << 2,
        Clipped = 1 << 3
	};
    
    enum class RenderShape : int32_t
    {
        Line,
        Quad,
        Text
    };
}
