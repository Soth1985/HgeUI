#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"

#include "ThGuiContextHge.h"

using namespace Thor;

bool FrameFunc();
bool RenderFunc();

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
			ThRectf drawArea = Util::MakeRect(0.0, 0.0, screenWidth, screenHeight);
			m_GuiCtx->SetDrawArea(drawArea);
			ThFontHandle font = m_GuiCtx->CreateTextFont("font1.fnt");
			m_GuiCtx->SetDefaultFont(font);
			CreatePanels();
            ThTexHandle cursorTex = m_GuiCtx->CreateTexture("cursor.png");
            m_Cursor = new hgeSprite(cursorTex, 0, 0, 32, 32);
			m_Hge->System_Start();			
		}

		Shutdown();
	}
    
    void Test()
    {
        ThGuiTextPtr text = std::make_shared<ThGuiText>(m_GuiCtx.get());
        text->SetText("Some text");
        text->SetPosition(Util::MakeDim2(0.5, 0, 0.5, 0));
        text->SetSize(Util::MakeDim2(0.25, 0, 0.25, 0));
        text->SetColor(ThColor(255, 0, 0, 255));
        text->SetBorderColor(ThColor(0, 0, 0, 255));
        text->SetBorderWidth(1.0);
        text->SetVertTextAlignment(TextVertAlignment::Center);
        text->SetHorTextAlignment(TextHorAlignment::Center);
        text->SetTextScale(0.5);
        
        m_GuiCtx->GetRootElement()->PushChild(text);
    }
    
    void CreatePanels()
    {
        ThGuiElementPtr panel1 = std::make_shared<ThGuiElement>(m_GuiCtx.get());
        panel1->SetColor(ThColor(128, 128, 128, 255));
        panel1->SetPosition(Util::MakeDim2(0.0, 0, 0.0, 0));
        panel1->SetSize(Util::MakeDim2(0.5, 0, 0.25, 0));
        
        ThGuiElementPtr panel2 = std::make_shared<ThGuiElement>(m_GuiCtx.get());
        panel2->SetColor(ThColor(128, 128, 128, 255));
        panel2->SetPosition(Util::MakeDim2(0.0, 0, 0.5, 0));
        panel2->SetSize(Util::MakeDim2(0.5, 0, 0.25, 0));
        
        m_GuiCtx->GetRootElement()->PushChild(panel1);
        m_GuiCtx->GetRootElement()->PushChild(panel2);
        
        FillPanel(panel1, panel2, mdc_OnBtnPress1, mdc_OnMouseEnterImg1, mdc_OnMouseLeaveImg1, "btn_off.png", "btn_click.png", "zazaka.png", "bg.png");
        
        FillPanel(panel2, panel1, mdc_OnBtnPress2, mdc_OnMouseEnterImg2, mdc_OnMouseLeaveImg2, "btn_off.png", "btn_click.png", "objects.png", "particles.png");
    }
    
    void FillPanel(ThGuiElementPtr panel, ThGuiElementPtr otherPanel, ThDelegateConnection& btnDel, ThDelegateConnection& imgEnterDel, ThDelegateConnection& imgLeaveDel, const std::string& btnImg, const std::string& btnPressedImg, const std::string& img1, const std::string& img2)
    {
        ThTexHandle btnTex = m_GuiCtx->CreateTexture(btnImg);
        ThTexHandle btnPressedTex = m_GuiCtx->CreateTexture(btnPressedImg);
        ThTexHandle img1Tex = m_GuiCtx->CreateTexture(img1);
        ThTexHandle img2Tex = m_GuiCtx->CreateTexture(img2);
        const float oneThird = 1.0 / 3.0;
        
        ThGuiButtonPtr button = std::make_shared<ThGuiButton>(m_GuiCtx.get());
        button->SetSize(Util::MakeDim2(0, 120, 0, 35));
		button->GetCaption()->SetTextScale(0.75);
		button->GetCaption()->SetText("Press me!");
        ThViewStateData buttonView;
        buttonView.m_Texture = btnTex;
        button->GetStates().SetStateData(WidgetViewState::NumStates, buttonView);
        buttonView.m_Texture = btnPressedTex;
        button->GetStates().SetStateData(WidgetViewState::Pressed, buttonView);
        btnDel = button->md_OnMouseButtonPressed.Connect([=](ThGuiElement* sender, MouseButton btn)
		{
			if (btn == MouseButton::Left)
			{
				bool invisible = otherPanel->IsStateSet((int32_t)WidgetState::Invisible);
				otherPanel->SetState(!invisible, (int32_t)WidgetState::Invisible);
			}            
        });
        
        ThGuiElementPtr image1 = std::make_shared<ThGuiElement>(m_GuiCtx.get());
        image1->SetPosition(Util::MakeDim2(oneThird, 0, 0.0, 0));
        image1->SetSize(Util::MakeDim2(oneThird, 0, 1.0, 0));
		
        if (img1Tex)
            image1->SetTexture(img1Tex);
        else
            image1->SetColor(ThColor(0, 255, 0, 255));
        
        ThGuiElementPtr image2 = std::make_shared<ThGuiElement>(m_GuiCtx.get());
        image2->SetState(true, (int32_t)WidgetState::Invisible);
        image2->SetPosition(Util::MakeDim2(2.0 * oneThird, 0, 0.0, 0));
        image2->SetSize(Util::MakeDim2(oneThird, 0, 1.0, 0));
        if (img2Tex)
            image2->SetTexture(img2Tex);
        else
            image2->SetColor(ThColor(0, 0, 255, 255));
        
		imgEnterDel = image1->md_OnMouseEnter.Connect([=](ThGuiElement* sender, float x, float y)
		{
            image2->SetState(false, (int32_t)WidgetState::Invisible);
        });
        
		imgLeaveDel = image1->md_OnMouseLeave.Connect([=](ThGuiElement* sender, float x, float y)
		{
            image2->SetState(true, (int32_t)WidgetState::Invisible);
        });
        
        panel->PushChild(button);
        panel->PushChild(image1);
        panel->PushChild(image2);
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
	ThGuiContextPtr m_GuiCtx;
    ThDelegateConnection mdc_OnMouseEnterImg1;
	ThDelegateConnection mdc_OnMouseLeaveImg1;
    ThDelegateConnection mdc_OnBtnPress1;
    ThDelegateConnection mdc_OnMouseEnterImg2;
	ThDelegateConnection mdc_OnMouseLeaveImg2;
    ThDelegateConnection mdc_OnBtnPress2;
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
