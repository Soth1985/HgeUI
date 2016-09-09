#pragma once

namespace Thor
{
	struct ThColor
	{
		ThColor()
			:
		m_R(0),
		m_G(0),
		m_B(0),
		m_A(0)
		{

		}

		ThColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
			:
		m_R(r),
		m_G(g),
		m_B(b),
		m_A(a)
		{

		}

		uint32_t ToArgb()const
		{
			return (uint32_t(m_A) << 24) + (uint32_t(m_R) << 16) + (uint32_t(m_G) << 8) + uint32_t(m_B);
		}

		uint8_t m_R;
		uint8_t m_G;
		uint8_t m_B;
		uint8_t m_A;
	};
}
