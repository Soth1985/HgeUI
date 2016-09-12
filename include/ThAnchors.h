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
		ThDim2 m_Offset;
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
		void SolveConstraints(ThGuiElement* elem, ThRectf& rect, const ThRectf& parentRect);        
		ThVec2f GetTargetPoint(ThGuiElement* elem, Anchor targetPoint, ThElementID targetElement);
		void ClearAnchors();
        
        ThAnchorData m_Data[(int32_t)Anchor::NumAnchors];
        ThConstrainedPosition m_TopLeft;
        ThConstrainedPosition m_BottomRight;
    };
}