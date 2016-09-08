#include "ThGuiContextHge.h"

using namespace Thor

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
    for (auto it = m_Textures.begin(); i != m_Textures.end(); ++it)
    {
        m_Hge->Texture_Free(it->second);
    }
}

void Log(const char* format, ...)override
{
    m_Hge->System_Log(format, ...);
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
    m_Input.m_Mouse.m_Wheel = m_Hge->Input_GetMouseWheel();
    
    struct KeyMap
    {
        MouseButton from;
        int32_t to;
    };
    
    static KeyMap mouseKeys[] =
    {
        {Left, HGEK_LBUTTON},
        {Middle, HGEK_MBUTTON},
        {Right, HGEK_RBUTTON},
    };
    
    static int32_t numMouseButtons = sizeof (mouseKeys) / sizeof (KeyMap);
    
    for (int32_t i = 0; i < numMouseButtons; ++i)
    {
        m_Input.SetMouseButtonState(mouseKeys[i].from, false, InputButtonState::JustPressed);
        m_Input.SetMouseButtonState(mouseKeys[i].from, false, InputButtonState::JustReleased);
        bool newState = m_Hge->Input_GetKeyState(mouseKeys[i].to);
        bool oldState = m_Input.GetMouseButtonState(mouseKeys[i].from, InputButtonState::Down);
        
        if (newState != oldState)
        {
            if (newState)
            {
                m_Input.SetMouseButtonState(mouseKeys[i].from, true, InputButtonState::Down | InputButtonState::JustPressed);
            }
            else
            {
                m_Input.SetMouseButtonState(mouseKeys[i].from, false, InputButtonState::Down);
                m_Input.SetMouseButtonState(mouseKeys[i].from, true, InputButtonState::JustPressed);
            }
        }
    }
}

void ThGuiContextHge::RenderImpl()
{
    
}