#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	namespace Util
    {
        static ThVec2f GetAbsoluteDimension(const ThDim2& relativeDim, const ThVec2f& parentDim, float pixelScale)
        {
            float x = relativeDim.X().AbsoluteDimension(parentDim.X(), pixelScale);
            float y = relativeDim.Y().AbsoluteDimension(parentDim.Y(), pixelScale);
            return ThVec2f(x, y);
        }

		static ThDim2 MakeDim2(float xR, int xA, float yR, int yA)
		{
			return ThDim2(ThDim(xR, xA), ThDim(yR, yA));
		}

		static ThDimRect MakeDimRect(float tlXR, int tlXA, float tlYR, int tlYA, float brXR, int brXA, float brYR, int brYA)
		{
			return ThDimRect(MakeDim2(tlXR, tlXA, tlYR, tlYA), MakeDim2(brXR, brXA, brYR, brYA));
		}

		static ThRectf MakeRect(float tlX, float tlY, float brX, float brY)
		{
			return ThRectf(ThVec2f(tlX, tlY), ThVec2f(brX, brY));
		}

		static ThDim2 Fill()
		{
			return MakeDim2(1.0, 0, 1.0, 0);
		}

		static void DecomposeRect(const ThRectf& rect, ThVec2f points[4])
		{
			ThVec2f size = rect.Size();
			points[0] = rect.TopLeft(); //tl
			points[1] = points[0] + ThVec2f(size.X(), 0.0); //tr
			points[2] = points[1] + ThVec2f(0.0, size.Y()); //br
			points[3] = points[2] - ThVec2f(size.X(), 0.0); //bl
		}
        
        static ThVec2f GetAnchorPoint(Anchor point, const ThRectf& rect)
        {
			ThVec2f points[4];
			DecomposeRect(rect, points);
            
            switch (point)
            {
                case Anchor::TopLeft:
                    return points[0];
                case Anchor::Top:
                    return (points[0] + points[1]) * 0.5;
                case Anchor::TopRight:
                    return points[1];
                case Anchor::Left:
                    return (points[0] + points[3]) * 0.5;
                case Anchor::Center:
                    return (points[0] + points[2]) * 0.5;
                case Anchor::Right:
                    return (points[1] + points[2]) * 0.5;
                case Anchor::BottomLeft:
                    return points[3];
                case Anchor::Bottom:
                    return (points[2] + points[3]) * 0.5;
                case Anchor::BottomRight:
                    return points[2];
            }
            
            return ThVec2f();
        }

		static ThVec2f Round(const ThVec2f& vec)
		{
			ThVec2f result;
			result.X() = round(vec.X());
			result.Y() = round(vec.Y());
			return result;
		}
    }
}