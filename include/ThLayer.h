#pragma once

#include <stdint.h>

namespace Thor
{
	struct ThLayer
    {
        ThLayer()
            :
        m_Index(0)
        {
            
        }
        
        ThLayer(uint16_t layer, uint16_t order)
        {
            SetLayer(layer);
            SetOrder(order);
        }
        
        void SetLayer(uint16_t layer)
        {
            uint32_t layer32 = (uint32_t)layer << 16;
            m_Index = (m_Index & s_OrderMask) | layer32;
        }
        
        void SetOrder(uint16_t order)
        {
            m_Index = (m_Index & s_LayerMask) | order;
        }
        
        uint16_t GetLayer()const
        {
            return (uint16_t)(m_Index >> 16);
        }
        
        uint16_t GetOrder()const
        {
            return (uint16_t)(m_Index & s_OrderMask);
        }
        
        bool operator<(const ThLayer& rhs)const
        {
            return m_Index < rhs.m_Index;
        }
        
        uint32_t m_Index;
    private:
        static const uint32_t s_OrderMask = 0x0000FFFF;
        static const uint32_t s_LayerMask = 0xFFFF0000;
    };
}