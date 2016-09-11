#pragma once

#include "ThGuiForward.h"

namespace Thor
{
	struct ThAnchorData
	{
        ThAnchorData()
        :
        m_TargetPoint(Anchor::NumPoints),
        m_TargetElement(0)
        {
            
        }
        
        Anchor m_TargetPoint;
        ThGuiElementID m_TargetElement;
        
	};
    
    struct ThConstrainedPosition
    {
        void Translate(const ThVec2f& offset)
        {
            ThVec2f clampedOffset(offset);
            offset.X() = m_ConstraintX.Clamp(offset.X());
            offset.Y() = m_ConstraintY.Clamp(offset.Y());
            m_Position += clampedOffset;
        }
        
        void Reset(const ThVec2f& position)
        {
            m_Position = position;
            m_ConstraintX.Min() = -FLT_MAX;
            m_ConstraintX.Max() = FLT_MAX;
            m_ConstraintY.Min() = -FLT_MAX;
            m_ConstraintY.Max() = FLT_MAX;
        }
        
        ThVec2f m_Position;
        ThRange<float> m_ConstraintX;
        ThRange<float> m_ConstraintY;
    };
    
    struct ThAnchors
    {
        void SolveConstraints(ThGuiElement* elem, ThRect& rect)
        {
            m_TopLeft.Reset(rect.TopLeft());
            m_BottomRight.Reset(rect.BottomRight());
            
            for (int32_t i = 0; i < NumPoints; ++i)
            {
                if (m_Data[i].m_TargetPoint != Anchor::NumPoints)
                {
                    ThVec2f targetPoint = GetTargetPoint(elem, m_Data[i].m_TargetPoint, m_Data[i].m_TargetElement);
                    ThVec2 point = Util::GetAnchorPoint(i, rect);
                    ThVec2f offset = targetPoint - point;
                    m_TopLeft.Translate(offset);
                    m_BottomRight.Translate(offset);
                    ThRange<float> newTlConstraintX;
                    ThRange<float> newTlConstraintY;
                    ThRange<float> newBrConstraintX;
                    ThRange<float> newBrConstraintY;
                    
                    switch (m_Data[i].m_TargetPoint)
                    {
                        case Anchor::TopLeft:
                        {
                            newTlConstraintX.Set(0.0, 0.0);
                            newTlConstraintY.Set(0.0, 0.0);
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::Top:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(0.0, 0.0);
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::TopRight:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(0.0, 0.0);
                            newBrConstraintX.Set(0.0, 0.0);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::Left:
                        {
                            newTlConstraintX.Set(0.0, 0.0);
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::Center:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::Right:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(0.0, 0.0);
                            newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
                            break;
                        }
                        case Anchor::BottomLeft:
                        {
                            newTlConstraintX.Set(0.0, 0.0);
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(0.0, 0.0);
                            break;
                        }
                        case Anchor::Bottom:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
                            newBrConstraintY.Set(0.0, 0.0);
                            break;
                        }
                        case Anchor::BottomRight:
                        {
                            newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
                            newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
                            newBrConstraintX.Set(0.0, 0.0);
                            newBrConstraintY.Set(0.0, 0.0);
                            break;
                        }
                    }
                    
                    rect.TopLeft() = m_TopLeft.m_Position;
                    rect.BottomRight() = m_BottomRight.m_Position;
                    m_TopLeft.m_ConstraintX.Intersect(newTlConstraintX);
                    m_TopLeft.m_ConstraintY.Intersect(newTlConstraintY);
                    m_BottomRight.m_ConstraintX.Intersect(newBrConstraintX);
                    m_BottomRight.m_ConstraintY.Intersect(newBrConstraintY);
                }
            }
        }
        
        ThVec2f GetTargetPoint(ThGuiElement* elem, Anchor targetPoint, ThGuiElementID targetElement)
        {
            ThGuiElement* parent = elem->GetParent();
            
            if (parent)
            {
                if (parent->GetElementID() == targetElement)
                    return Util::GetAnchorPoint(targetPoint, parent->GetRealRect());
                
                ThGuiElementPtr child = parent->GetChild();
                
                if (child && child->GetElementID() == targetElement)
                    return Util::GetAnchorPoint(targetPoint, child->GetRealRect());
            }
            
            return Util::GetAnchorPoint(targetPoint, elem->GetRealRect());
        }
        
        ThAnchorData m_Data[Anchor::NumAnchors];
        ThConstrainedPosition m_TopLeft;
        ThConstrainedPosition m_BottomRight;
    };
}