#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	namespace Util
    {
        static ThVec2f GetAbsoluteDimension(const ThDim2& relativeDim, const ThVec2f& parentDim)
        {
            float x = relativeDim.X().AbsoluteDimension(parentDim.X());
            float y = relativeDim.Y().AbsoluteDimension(parentDim.Y());
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
    }
}