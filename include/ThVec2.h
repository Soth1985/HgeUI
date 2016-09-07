#pragma once

namespace Thor
{
	template <class T>
	struct ThVec2
	{
		typedef T ValueType;

		ThVec2()
			:
		m_X(0.0),
		m_Y(0.0)
		{
		}

		ThVec2(const T& x, const T& y)
			:
		m_X(x),
		m_Y(y)
		{

		}

		const T& X()const
		{
			return m_X;
		}

		T& X()
		{
			return m_X;
		}

		const T& Y()const
		{
			return m_Y;
		}

		T& Y()
		{
			return m_Y;
		}

		ThVec2 operator+(const ThVec2& rhs)
		{
			return ThVec2(m_X + rhs.m_X, m_Y + rhs.m_Y);
		}

		ThVec2 operator-(const ThVec2& rhs)
		{
			return ThVec2(m_X - rhs.m_X, m_Y - rhs.m_Y);
		}

		ThVec2 operator*(const ThVec2& rhs)
		{
			return ThVec2(m_X * rhs.m_X, m_Y * rhs.m_Y);
		}

		ThVec2 operator*(const T& rhs)
		{
			return ThVec2(m_X * rhs, m_Y * rhs);
		}

		ThVec2 operator/(const T& rhs)
		{
			return ThVec2(m_X / rhs, m_Y / rhs);
		}

		T m_X;
		T m_Y;
	};
}