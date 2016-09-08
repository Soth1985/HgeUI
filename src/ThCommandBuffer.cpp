#pragma once

#include "ThCommandBuffer.h"
#include <vector>

using namespace Thor;

ThCommandBuffer::ThCommandBuffer()
{
    
}

void ThCommandBuffer::PushState(const ThRectf& clipRect)
{
    m_States.push_back(ThRenderState{clipRect});
    m_StateStack.push(m_States.size() - 1);
}

void ThCommandBuffer::PopState()
{
    m_StateStack.pop();
}

void ThCommandBuffer::AddQuad(const ThRectf& shape, ThTexHandle tex, ThLayer layer, const ThColor& color)
{
	ThDrawShapeCmd cmd;
    cmd.m_Quad.m_Shape = shape;
    cmd.m_Quad.m_Texture = tex;
    cmd.m_ShapeType = RenderShape::Quad;
    cmd.m_Color = color;
    cmd.m_Layer = layer;
    cmd.m_StateIndex = m_StateStack.top();
	m_Shapes.push_back(cmd);
}

void ThCommandBuffer::AddLine(const ThVec2f& from, const ThVec2f& to, float width, ThLayer layer, const ThColor& color)
{
    m_Shapes.push_back(ThDrawShapeCmd());
    ThDrawShapeCmd cmd = m_Shapes.back();
    cmd.m_Line.m_From = from;
    cmd.m_Line.m_To = to;
    cmd.m_Line.m_Width = width;
    cmd.m_ShapeType = RenderShape::Line;
    cmd.m_Color = color;
    cmd.m_Layer = layer;
    cmd.m_StateIndex = m_StateStack.top();
}

void ThCommandBuffer::SortByLayer()
{
    std::stable_sort(m_Shapes.begin(), m_Shapes.end());
}

void ThCommandBuffer::Reset()
{
    m_States.clear();
    m_Shapes.clear();

	while (!m_StateStack.empty())
	{
		m_StateStack.pop();
	}
	
	m_StateStack.push(-1);
}