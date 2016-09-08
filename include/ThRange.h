#pragma once

#include <algorithm>

namespace Thor
{

class Range
{
public:

	Range()
		:
	m_Min(0.0f),
	m_Max(0.0f)
	{

	}

	Range(float min, float max)
	{
		m_Min = (std::min)(min, max);
		m_Max = (std::max)(min, max);
	}

	bool Overlap(const Range& r)const
	{
		return r.GetMin() <= m_Max && m_Min <= r.GetMax();
	}

	void Join(const Range& r)
	{
		m_Min = m_Min < r.GetMin() ? m_Min : r.GetMin();
		m_Max = m_Max > r.GetMax() ? m_Max : r.GetMax();
	}

	float GetMin()const
	{
		return m_Min;
	}

	float GetMax()const
	{
		return m_Max;
	}
    
    float Clamp(float val)
    {
        if (val < m_Min)
            return m_Min;
        else if (val > m_Max)
            return m_Max;
        else
            return val;
    }

private:

	float m_Min;
	float m_Max;
};

}