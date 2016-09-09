#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"

#include "ThGuiContextHge.h"

using namespace Thor;

bool FrameFunc();
bool RenderFunc();
bool FocusLostFunc();

class ThSampleApp
{
public:
	ThSampleApp()
		:
	m_Hge(nullptr),
    m_Cursor(nullptr)
	{

	}

	void Start(uint32_t screenWidth, uint32_t screenHeight)
	{
		m_Hge = hgeCreate(HGE_VERSION);

		m_Hge->System_SetState(HGE_LOGFILE, "hge_gui.log");
		m_Hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		m_Hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
		m_Hge->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
		m_Hge->System_SetState(HGE_TITLE, "Sample app");
		m_Hge->System_SetState(HGE_FPS, 100);
		m_Hge->System_SetState(HGE_WINDOWED, true);
		m_Hge->System_SetState(HGE_SCREENWIDTH, screenWidth);
		m_Hge->System_SetState(HGE_SCREENHEIGHT, screenHeight);
		m_Hge->System_SetState(HGE_SCREENBPP, 32);

		if (m_Hge->System_Initiate())
		{
			m_GuiCtx = std::make_shared<ThGuiContextHge>(m_Hge);
			m_GuiCtx->Init();
			ThRectf drawArea(ThVec2f(0.0, 0.0), ThVec2f(screenWidth, screenHeight));
			m_GuiCtx->SetDrawArea(drawArea);

			m_Font = m_GuiCtx->CreateTextFont("font1.fnt");
            ThTexHandle cursorTex = m_GuiCtx->CreateTexture("cursor.png");
            m_Cursor = new hgeSprite(cursorTex, 0, 0, 32, 32);
			m_Hge->System_Start();			
		}

		Shutdown();
	}

	bool Update()
	{
		// Process keys
		if (m_Hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			return true;
		}

		if (m_GuiCtx)
			m_GuiCtx->Update();

		return false;
	}

	bool Render()
	{
		m_Hge->Gfx_BeginScene();
		m_Hge->Gfx_Clear(0);

		if (m_GuiCtx)
			m_GuiCtx->Render();
		
		if (m_Hge->Input_IsMouseOver())
		{
			ThVec2f mousePos = m_GuiCtx->GetInput().GetMousePos();
			m_Cursor->Render(mousePos.X(), mousePos.Y());
		}
        
		//((hgeFont*)m_Font)->printf(5, 5, HGETEXT_LEFT, "x=%.3f, y=%.3f\n", mousePos.X(), mousePos.Y());
		m_Hge->Gfx_EndScene();

		return false;
	}
private:
	void Shutdown()
	{
		if (m_GuiCtx)
		{
			m_GuiCtx->Shutdown();
			m_GuiCtx = nullptr;
		}
		delete m_Cursor;
		m_Hge->System_Shutdown();
		m_Hge->Release();
	}

	HGE* m_Hge;
    hgeSprite* m_Cursor;
    ThFontHandle m_Font;
	ThGuiContextPtr m_GuiCtx;
};

ThSampleApp g_App;

bool FrameFunc()
{
	return g_App.Update();
}

bool RenderFunc()
{
	return g_App.Render();
}

bool FocusLostFunc()
{
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	g_App.Start(800, 600);
	return 0;
}
