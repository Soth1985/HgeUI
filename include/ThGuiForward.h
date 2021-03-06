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

	static const ThColor EmptyColor;
	static const ThColor WhiteColor(255, 255, 255, 255);
	static const ThDim2 EmptyDim2;

	class ThGuiContext;
	typedef std::shared_ptr<ThGuiContext> ThGuiContextPtr;
	typedef std::weak_ptr<ThGuiContext> ThGuiContextWeakPtr;

	class ThGuiElement;
	typedef std::shared_ptr<ThGuiElement> ThGuiElementPtr;
	typedef std::weak_ptr<ThGuiElement> ThGuiElementWeakPtr;

	class ThGuiButton;
	typedef std::shared_ptr<ThGuiButton> ThGuiButtonPtr;
	typedef std::weak_ptr<ThGuiButton> ThGuiButtonWeakPtr;

	class ThGuiText;
	typedef std::shared_ptr<ThGuiText> ThGuiTextPtr;
	typedef std::weak_ptr<ThGuiText> ThGuiTextWeakPtr;

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
		Panel,
        Text
	};

	enum class WidgetState : int32_t
	{
		LayoutRequired = 1 << 0,
        Inactive = 1 << 1,
        Clipped = 1 << 2,
		Invisible = 1 << 3
	};
    
    enum class RenderShape : int32_t
    {
        Line,
        Quad,
        Text
    };

	enum class TextHorAlignment : int32_t
	{
		Left,
		Center,
		Right
	};

	enum class TextVertAlignment : int32_t
	{
		Top,
		Center,
		Bottom
	};
    
    enum class WidgetViewState : int32_t
    {
        Default,
        MouseOver,
        Pressed,
        NumStates
    };
    
    enum class WidgetLayer : uint16_t
    {
        Background,
        Normal,
        Overlay
    };
}
