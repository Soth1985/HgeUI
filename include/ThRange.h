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
		m_Min = (std::min)(min, max);
		m_Max = (std::max)(min, max);
	}

	bool Overlap(const ThRange& r)const
	{
		return r.GetMin() <= m_Max && m_Min <= r.GetMax();
	}

	void Join(const ThRange& r)
	{
		m_Min = m_Min < r.GetMin() ? m_Min : r.GetMin();
		m_Max = m_Max > r.GetMax() ? m_Max : r.GetMax();
	}

	T GetMin()const
	{
		return m_Min;
	}

	T GetMax()const
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