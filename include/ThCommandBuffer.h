#pragma once

#include "ThGuiForward.h"
#include <vector>

namespace Thor
{
    struct ThRenderState
    {
        ThRectf m_ClipRect;
    };
    
    struct ThQuadShape
    {
        ThRectf m_Shape;
        ThTexHandle m_Texture;
    };
    
    struct ThLineShape
    {
        ThVec2f m_From;
        ThVec2f m_To;
        float m_Width;
    };
    
    struct ThTextShape
    {
        const char* m_Str;
    };
    
    struct ThDrawShapeCmd
    {
        bool operator<(const ThDrawShapeCmd& rhs)
        {
            return m_Layer < rhs.m_Layer;
        }
        
        union
        {
            ThQuadShape m_Quad;
            ThLineShape m_Line;
            ThTextShape m_Text;
        };
        
        RenderShape m_ShapeType;
        ThLayer m_Layer;
        int32_t m_StateIndex;
        ThColor m_Color;
    };
    
    class ThCommandBuffer
    {
    public:
        
        ThCommandBuffer();
        void PushState(const ThRectf& clipRect);
        void PopState();
        void AddQuad(const ThRectf& shape, ThTexHandle tex, ThLayer layer, const ThColor& color);
        void AddLine(const ThVec2f& from, const ThVec2f& to, float width, ThLayer layer, const ThColor& color);
        void SortByLayer();
        void Reset();
        
        std::vector<ThRenderState> m_States;
        std::vector<ThDrawShapeCmd> m_Shapes;
        std::stack<int32_t> m_StateStack;
    };
}