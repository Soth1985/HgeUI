#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"

#include "ThGuiContextHge.h"

using namespace Thor;

// Pointer to the HGE interface.
// Helper classes require this to work.
HGE* g_Hge = 0;
ThGuiContextPtr g_GuiCtx;

// Pointers to the HGE objects we will use
hgeSprite*			spr;
hgeSprite*			spt;
hgeFont*			fnt;
hgeParticleSystem*	par;

// Handles for HGE resourcces
HTEXTURE			tex;

bool FrameFunc()
{	
	float dt = g_Hge->Timer_GetDelta();

	// Process keys
	if (g_Hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		g_GuiCtx = nullptr;
		return true;
	}

	return false;
}

bool RenderFunc()
{
	// Render graphics
	g_Hge->Gfx_BeginScene();
	g_Hge->Gfx_Clear(0);
	par->Render();
	spr->Render(100, 100);
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", g_Hge->Timer_GetDelta(), g_Hge->Timer_GetFPS());
	g_Hge->Gfx_EndScene();

	return false;
}

void ShutDown()
{
	g_Hge->System_Shutdown();
	g_Hge->Release();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	g_Hge = hgeCreate(HGE_VERSION);

	g_Hge->System_SetState(HGE_LOGFILE, "hge_tut03.log");
	g_Hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	g_Hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	g_Hge->System_SetState(HGE_TITLE, "Sample app");
	g_Hge->System_SetState(HGE_FPS, 100);
	g_Hge->System_SetState(HGE_WINDOWED, true);
	g_Hge->System_SetState(HGE_SCREENWIDTH, 800);
	g_Hge->System_SetState(HGE_SCREENHEIGHT, 600);
	g_Hge->System_SetState(HGE_SCREENBPP, 32);

	if(g_Hge->System_Initiate()) 
	{
		tex = g_Hge->Texture_Load("particles.png");
		if(!tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load one of the following files:\nMENU.WAV, PARTICLES.PNG, FONT1.FNT, FONT1.PNG, TRAIL.PSI", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			ShutDown();
			return 0;
		}

		// Create and set up a sprite
		spr=new hgeSprite(0, 96, 64, 32, 32);
		spr->SetColor(0xFFFFA000);
		//spr->SetHotSpot(16,16);

		// Load a font
		fnt=new hgeFont("font1.fnt");

		// Create and set up a particle system
		spt=new hgeSprite(tex, 32, 32, 32, 32);
		spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		spt->SetHotSpot(16,16);
		par=new hgeParticleSystem("trail.psi",spt);
		par->Fire();

		// Let's rock now!
		g_Hge->System_Start();

		// Delete created objects and free loaded resources
		delete par;
		delete fnt;
		delete spt;
		delete spr;
		g_Hge->Texture_Free(tex);
	}

	ShutDown();
	return 0;
}
