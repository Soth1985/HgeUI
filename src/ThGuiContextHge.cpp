#include "ThGuiContextHge.h"
#include "ThGuiUtil.h"
#include "hgefont.h"

using namespace Thor;

ThGuiContextHge::ThGuiContextHge(HGE* hge)
    :
m_Hge(hge)
{
    
}

bool ThGuiContextHge::Init()
{
    return true;
}

void ThGuiContextHge::Shutdown()
{
    for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
    {
        m_Hge->Texture_Free(it->second);
    }
    
    for (auto it = m_Fonts.begin(); it != m_Fonts.end(); ++it)
    {
        delete it->second;
    }
}

void ThGuiContextHge::Log(const char* format, ...)
{
	va_list args;
	va_start(args, format);
    m_Hge->System_Log(format, args);
	va_end(args);
}

ThFontHandle ThGuiContextHge::CreateTextFont(const std::string& name)
{
    auto found = m_Fonts.find(name);
    
    if (found != m_Fonts.end())
        return (ThFontHandle)found->second;
    
    hgeFont* result = new hgeFont(name.c_str());
    m_Fonts[name] = result;
    return (ThFontHandle)result;
}

float ThGuiContextHge::GetFontHeight(ThFontHandle font)
{
    hgeFont* fontHge = (hgeFont*)font;
	return fontHge->GetHeight();
}

float ThGuiContextHge::GetStringWidth(ThFontHandle font, const std::string& text)
{
    hgeFont* fontHge = (hgeFont*)font;
    return fontHge->GetStringWidth(text.c_str());
}

ThTexHandle ThGuiContextHge::CreateTexture(const std::string& name)
{
    auto found = m_Textures.find(name);
    
    if (found != m_Textures.end())
        return found->second;
    
    HTEXTURE tex = m_Hge->Texture_Load(name.c_str());
    
    if (!tex)
    {
        Log("Failed to load texture %s\n", name.c_str());
        return 0;
    }
    else
    {
        m_Textures[name] = tex;
        return tex;
    }
}

void ThGuiContextHge::UpdateInputImpl()
{
    m_DeltaTime = m_Hge->Timer_GetDelta();
    m_Hge->Input_GetMousePos(&m_Input.m_Mouse.m_Pos.m_X, &m_Input.m_Mouse.m_Pos.m_Y);
    m_Input.m_Mouse.m_Wheel = (float)m_Hge->Input_GetMouseWheel();
    
    struct KeyMap
    {
        MouseButton from;
        int32_t to;
    };
    
    static KeyMap mouseKeys[] =
    {
        {MouseButton::Left, HGEK_LBUTTON},
        {MouseButton::Middle, HGEK_MBUTTON},
        {MouseButton::Right, HGEK_RBUTTON},
    };
    
    static int32_t numMouseButtons = sizeof (mouseKeys) / sizeof (KeyMap);
    
    for (int32_t i = 0; i < numMouseButtons; ++i)
    {
        m_Input.SetMouseButtonState(mouseKeys[i].from, false, (int32_t)InputButtonState::JustPressed);
        m_Input.SetMouseButtonState(mouseKeys[i].from, false, (int32_t)InputButtonState::JustReleased);
        bool newState = m_Hge->Input_GetKeyState(mouseKeys[i].to);
        bool oldState = m_Input.GetMouseButtonState(mouseKeys[i].from, (int32_t)InputButtonState::Down);
        
        if (newState != oldState)
        {
            if (newState)
            {
                m_Input.SetMouseButtonState(mouseKeys[i].from, true, (int32_t)InputButtonState::Down | (int32_t)InputButtonState::JustPressed);
            }
            else
            {
                m_Input.SetMouseButtonState(mouseKeys[i].from, false, (int32_t)InputButtonState::Down);
                m_Input.SetMouseButtonState(mouseKeys[i].from, true, (int32_t)InputButtonState::JustPressed);
            }
        }
    }
}

void ThGuiContextHge::RenderImpl()
{
	m_RenderBuf.SortByLayer();

	//m_Hge->Gfx_BeginScene();

	int32_t curState = -1;
	for (size_t i = 0; i < m_RenderBuf.m_Shapes.size(); ++i)
	{
		ThDrawShapeCmd& cmd = m_RenderBuf.m_Shapes[i];

		if (cmd.m_StateIndex != curState)
		{
			curState = cmd.m_StateIndex;

			if (curState >= 0)
			{
				ThRenderState& state = m_RenderBuf.m_States[curState];
				m_Hge->Gfx_SetClipping(state.m_ClipRect.TopLeft().X(), state.m_ClipRect.TopLeft().Y(), state.m_ClipRect.Width(), state.m_ClipRect.Height());
			}
			else
			{
				m_Hge->Gfx_SetClipping();
			}
		}

		switch (cmd.m_ShapeType)
		{
			case RenderShape::Quad:
			{
				hgeQuad quad;
				quad.tex = cmd.m_Quad.m_Texture;
				quad.blend = BLEND_DEFAULT;

				ThVec2f rectPoints[4];
				Util::DecomposeRect(cmd.m_Quad.m_Shape, rectPoints);

				quad.v[0].x = rectPoints[0].X(); quad.v[0].y = rectPoints[0].Y();
				quad.v[0].tx = 0.0; quad.v[0].ty = 0.0;

				quad.v[1].x = rectPoints[1].X(); quad.v[1].y = rectPoints[1].Y();
				quad.v[1].tx = 1.0; quad.v[1].ty = 0.0;

				quad.v[2].x = rectPoints[2].X(); quad.v[2].y = rectPoints[2].Y();
				quad.v[2].tx = 1.0; quad.v[2].ty = 1.0;

				quad.v[3].x = rectPoints[3].X(); quad.v[3].y = rectPoints[3].Y();
				quad.v[3].tx = 0.0; quad.v[3].ty = 1.0;

				quad.v[0].z = quad.v[1].z = quad.v[2].z = quad.v[3].z = 0.5f;
				quad.v[0].col = quad.v[1].col = quad.v[2].col = quad.v[3].col = cmd.m_Color.ToArgb();
				m_Hge->Gfx_RenderQuad(&quad);				
				break;
			}
			case RenderShape::Line:
			{
				m_Hge->Gfx_RenderLine(cmd.m_Line.m_From.X(), cmd.m_Line.m_From.Y(), cmd.m_Line.m_To.X(), cmd.m_Line.m_To.Y(), cmd.m_Color.ToArgb());
				break;
			}
			case RenderShape::Text:
			{
				break;
			}
		}
	}
	
	if (!m_RenderBuf.m_States.empty())
		m_Hge->Gfx_SetClipping();
	//m_Hge->Gfx_EndScene();
}