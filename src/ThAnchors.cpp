#include "ThAnchors.h"
#include "ThGuiElement.h"
#include "ThGuiContext.h"
#include "ThGuiUtil.h"

using namespace Thor;

void ThConstrainedPosition::Translate(const ThVec2f& offset)
{
	/*ThVec2f clampedOffset(offset);
	clampedOffset.X() = m_ConstraintX.Clamp(offset.X());
	clampedOffset.Y() = m_ConstraintY.Clamp(offset.Y());
	m_Position = m_Position + clampedOffset;*/

	m_Position = m_Position + offset;
	m_Position.X() = m_ConstraintX.Clamp(m_Position.X());
	m_Position.Y() = m_ConstraintY.Clamp(m_Position.Y());
}

void ThConstrainedPosition::Reset(const ThVec2f& position)
{
	m_Position = position;
	m_ConstraintX.Min() = -FLT_MAX;
	m_ConstraintX.Max() = FLT_MAX;
	m_ConstraintY.Min() = -FLT_MAX;
	m_ConstraintY.Max() = FLT_MAX;
}

void ThAnchors::ClearAnchors()
{
	for (int32_t i = 0; i < (int32_t)Anchor::NumAnchors; ++i)
	{
		m_Data[i].m_TargetPoint = Anchor::NumAnchors;
	}
}

void ThAnchors::SolveConstraints(ThGuiElement* elem, ThRectf& rect, const ThRectf& parentRect)
{
	m_TopLeft.Reset(rect.TopLeft());
	m_BottomRight.Reset(rect.BottomRight());

	for (int32_t i = 0; i < (int32_t)Anchor::NumAnchors; ++i)
	{
		if (m_Data[i].m_TargetPoint != Anchor::NumAnchors)
		{
			ThVec2f targetPoint = GetTargetPoint(elem, m_Data[i].m_TargetPoint, m_Data[i].m_TargetElement);
			ThVec2f point = Util::GetAnchorPoint((Anchor)i, rect);
			ThVec2f anchorOffset = Util::GetAbsoluteDimension(m_Data[i].m_Offset, parentRect.Size(), elem->GetContext()->GetPixelScale());
			ThVec2f offset = targetPoint - point + anchorOffset;
			m_TopLeft.Translate(offset);
			m_BottomRight.Translate(offset);
			ThRange<float> newTlConstraintX;
			ThRange<float> newTlConstraintY;
			ThRange<float> newBrConstraintX;
			ThRange<float> newBrConstraintY;

			switch ((Anchor)i)
			{
			case Anchor::TopLeft:
			{
				newTlConstraintX.Set(targetPoint.X(), targetPoint.X());
				newTlConstraintY.Set(targetPoint.Y(), targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
				newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
				break;
			}
			case Anchor::Top:
			{
				newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
				newTlConstraintY.Set(targetPoint.Y(), targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
				newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
				break;
			}
			case Anchor::TopRight:
			{
				newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
				newTlConstraintY.Set(targetPoint.Y(), targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), targetPoint.X());
				newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
				break;
			}
			case Anchor::Left:
			{
				newTlConstraintX.Set(targetPoint.X(), targetPoint.X());
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
				newBrConstraintX.Set(targetPoint.X(), targetPoint.X());
				newBrConstraintY.Set(targetPoint.Y(), FLT_MAX);
				break;
			}
			case Anchor::BottomLeft:
			{
				newTlConstraintX.Set(targetPoint.X(), targetPoint.X());
				newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
				newBrConstraintY.Set(targetPoint.Y(), targetPoint.Y());
				break;
			}
			case Anchor::Bottom:
			{
				newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
				newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), FLT_MAX);
				newBrConstraintY.Set(targetPoint.Y(), targetPoint.Y());
				break;
			}
			case Anchor::BottomRight:
			{
				newTlConstraintX.Set(-FLT_MAX, targetPoint.X());
				newTlConstraintY.Set(-FLT_MAX, targetPoint.Y());
				newBrConstraintX.Set(targetPoint.X(), targetPoint.X());
				newBrConstraintY.Set(targetPoint.Y(), targetPoint.Y());
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

ThVec2f ThAnchors::GetTargetPoint(ThGuiElement* elem, Anchor targetPoint, ThElementID targetElement)
{
	ThGuiElement* parent = elem->GetParent();

	if (parent)
	{
		if (parent->GetElementID() == targetElement)
			return Util::GetAnchorPoint(targetPoint, parent->GetRealRect());

		ThGuiElementPtr child = parent->GetChild(targetElement);

		if (child)
			return Util::GetAnchorPoint(targetPoint, child->GetRealRect());
	}

	return Util::GetAnchorPoint(targetPoint, elem->GetRealRect());
}