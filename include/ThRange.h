#pragma once

#include <algorithm>

namespace Thor
{

template <class T>
class ThRange
{
public:

	ThRange()
		:
	m_Min(0.0),
	m_Max(0.0)
	{

	}

	ThRange(T min, T max)
	{
        Set(min, max);
	}
    
    void Set(T min, T max)
    {
        m_Min = (std::min)(min, max);
        m_Max = (std::max)(min, max);
    }

	bool Overlap(const ThRange& r)const
	{
		return r.Min() <= m_Max && m_Min <= r.Max();
	}

	void Join(const ThRange& r)
	{
		m_Min = m_Min < r.Min() ? m_Min : r.Min();
		m_Max = m_Max > r.Max() ? m_Max : r.Max();
	}
    
    void Intersect(const ThRange& r)
    {
        if (Overlap(r))
        {
            m_Min = r.Clamp(m_Min);
            m_Max = r.Clamp(m_Max);
        }
        else
        {
            m_Min = 0.0;
            m_Max = 0.0;
        }
    }

	const T& Min()const
	{
		return m_Min;
	}

	const T& Max()const
	{
		return m_Max;
	}
    
    T& Min()
    {
        return m_Min;
    }
    
    T& Max()
    {
        return m_Max;
    }
    
    T Clamp(T val)
    {
        if (val < m_Min)
            return m_Min;
        else if (val > m_Max)
            return m_Max;
        else
            return val;
    }

private:

	T m_Min;
	T m_Max;
};

}