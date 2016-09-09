#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"

#include "ThGuiContextHge.h"

using namespace Thor;

bool FrameFunc();
bool RenderFunc();

// Pointers to the HGE objects we will use
hgeFont*			fnt;

class ThSampleApp
{
public:
	ThSampleApp()
		:
	m_Hge(nullptr)
	{

	}

	void Start(uint32_t screenWidth, uint32_t screenHeight)
	{
		m_Hge = hgeCreate(HGE_VERSION);

		m_Hge->System_SetState(HGE_LOGFILE, "hge_gui.log");
		m_Hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		m_Hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
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

			// Load a font
			fnt = new hgeFont("font1.fnt");

			// Let's rock now!
			m_Hge->System_Start();			
		}

		Shutdown();
	}

	bool Update()
	{
		float dt = m_Hge->Timer_GetDelta();

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

		fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", m_Hge->Timer_GetDelta(), m_Hge->Timer_GetFPS());
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
		delete fnt;
		m_Hge->System_Shutdown();
		m_Hge->Release();
	}

	HGE* m_Hge;
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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	g_App.Start(800, 600);
	return 0;
}
