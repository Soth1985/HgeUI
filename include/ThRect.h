#pragma once

#include "ThVec2.h"

namespace Thor
{
	template <class T>
	struct ThRect
	{
		typedef typename T::ValueType ValueType;
        typedef ThVec2<ValueType> Vec2;

		ThRect()
		{

		}

		ThRect(const T& topLeft, const T& bottomRight)
			:
		m_TopLeft(topLeft),
		m_BottomRight(bottomRight)
		{

		}

		const T& TopLeft()const
		{
			return m_TopLeft;
		}

		T& TopLeft()
		{
			return m_TopLeft;
		}

		const T& BottomRight()const
		{
			return m_BottomRight;
		}

		T& BottomRight()
		{
			return m_BottomRight;
		}

		T Width()const
		{
			return (m_BottomRight - m_TopLeft).X();
		}

		T Height()const
		{
			return (m_BottomRight - m_TopLeft).Y();
		}
        
        Vec2 Size()const
        {
            return m_BottomRight - m_TopLeft;
        }

		T m_TopLeft;
		T m_BottomRight;
	};
}