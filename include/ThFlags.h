#pragma once

#include <stdint.h>

namespace Thor
{
    
    template <class T>
    class ThFlags
    {
    public:
        
        ThFlags(T bits)
            :
        m_BitField(bits)
        {
        }
        
        ThFlags()
            :
        m_BitField(0)
        {
        }
        
        void	SetFlag(bool state, T flag)
        {
            if(state)
                m_BitField |= flag;
            else
                m_BitField &= ~flag;
        }
        
        bool	CheckOneFlag(T flag)const
        {
            return ( m_BitField & flag ) == flag;
        }

		bool	CheckFlags(T flags)const
		{
			return (m_BitField & flags) != 0;
		}
        
        void	Reset()
        {
            m_BitField=0;
        }
        
        const T& GetBitField()const
        {
            return m_BitField;
        }
        
    private:
        T m_BitField;
    };
    
}//Thor