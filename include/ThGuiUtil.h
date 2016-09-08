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
    }
}