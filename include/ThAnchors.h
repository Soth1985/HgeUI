#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	struct ThAnchorData
	{
        ThAnchorData()
        :
        m_TargetPoint(Anchor::NumAnchors),
        m_TargetElement(0)
        {
            
        }
        
        Anchor m_TargetPoint;
        ThElementID m_TargetElement;        
	};
    
    struct ThConstrainedPosition
    {
		void Translate(const ThVec2f& offset);
        
		void Reset(const ThVec2f& position);
        
        ThVec2f m_Position;
        ThRange<float> m_ConstraintX;
        ThRange<float> m_ConstraintY;
    };
    
    struct ThAnchors
    {
		void SolveConstraints(ThGuiElement* elem, ThRectf& rect);
        
		ThVec2f GetTargetPoint(ThGuiElement* elem, Anchor targetPoint, ThElementID targetElement);
        
        ThAnchorData m_Data[(int32_t)Anchor::NumAnchors];
        ThConstrainedPosition m_TopLeft;
        ThConstrainedPosition m_BottomRight;
    };
}