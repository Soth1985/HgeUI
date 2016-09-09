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

		ValueType Width()const
		{
			return (m_BottomRight - m_TopLeft).X();
		}

		ValueType Height()const
		{
			return (m_BottomRight - m_TopLeft).Y();
		}
        
        Vec2 Size()const
        {
            return m_BottomRight - m_TopLeft;
        }

		bool IsInside(const Vec2& point)const
		{
			return	(point.X() >= m_TopLeft.X()) && 
					(point.X() <= m_BottomRight.X()) &&
					(point.Y() >= m_TopLeft.Y()) &&
					(point.Y() <= m_BottomRight.Y())
		}
        
        ValueType Area()const
        {
            Vec2 size = Size();
            return size.X() * size.Y();
        }
        
        bool Intersects(const ThRect& rhs)const
        {
            Vec2 size = Size();
            Vec2 rhsSize = rhs.Size();
            ThRange<T> rngX(m_TopLeft.X(), m_TopLeft.X() + size.X());
            ThRange<T> rngY(m_TopLeft.Y(), m_TopLeft.Y() + size.Y());
            ThRange<T> rhsRngX(rhs.m_TopLeft.X(), rhs.m_TopLeft.X() + rhsSize.X());
            ThRange<T> rhsRngX(rhs.m_TopLeft.Y(), rhs.m_TopLeft.Y() + rhsSize.Y());
            
            return rngX.Overlaps(rhsRngX) && rngY.Overlaps(rhsRngY);
        }

		T m_TopLeft;
		T m_BottomRight;
	};
}