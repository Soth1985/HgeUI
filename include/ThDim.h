#pragma once

#include <stdint.h>

namespace Thor
{
	struct ThDim
	{
		ThDim()
			:
		m_Rel(0.0),
		m_Abs(0)
		{
		}

		ThDim(float rel, int32_t abs)
			:
		m_Rel(rel),
		m_Abs(abs)
		{

		}
        
        ThDim(float rel)
            :
        m_Rel(rel),
        m_Abs(0)
        {
            
        }
        
        ThDim(int abs)
            :
        m_Rel(0.0),
        m_Abs(abs)
        {
            
        }

		float Rel()const
		{
			return m_Rel;
		}

		float& Rel()
		{
			return m_Rel;
		}

		int32_t Abs()const
		{
			return m_Abs;
		}

		int32_t& Abs()
		{
			return m_Abs;
		}

		ThDim operator+(const ThDim& rhs)
		{
			return ThDim(m_Rel + rhs.m_Rel, m_Abs + rhs.m_Abs);
		}

		ThDim operator-(const ThDim& rhs)
		{
			return ThDim(m_Rel - rhs.m_Rel, m_Abs - rhs.m_Abs);
		}

		ThDim operator*(const ThDim& rhs)
		{
			return ThDim(m_Rel * rhs.m_Rel, m_Abs * rhs.m_Abs);
		}

		ThDim operator*(float rhs)
		{
			return ThDim(m_Rel * rhs, m_Abs * rhs);
		}

		ThDim operator/(float rhs)
		{
			return ThDim(m_Rel / rhs, m_Abs / rhs);
		}
        
        float Dimension(int size)
        {
            return m_Rel * size + m_Abs;
        }

		float m_Rel;
		int32_t m_Abs;
	};
}