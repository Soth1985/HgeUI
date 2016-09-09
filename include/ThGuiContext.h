#pragma once

#include "ThGuiForward.h"
#include "ThCommandBuffer.h"
#include "ThInput.h"
#include <string>

namespace Thor
{
	class ThGuiContext : public std::enable_shared_from_this<ThGuiContext>
	{
	public:
        ThGuiContext();
		virtual ~ThGuiContext();
		virtual ThTexHandle CreateTexture(const std::string& name) = 0;
        virtual ThFontHandle CreateTextFont(const std::string& name) = 0;
        virtual float GetFontHeight(ThFontHandle font) = 0;
        virtual float GetStringWidth(ThFontHandle font, const std::string& text) = 0;
        virtual bool Init() = 0;
        virtual void Shutdown() = 0;
        virtual void Log(const char* format, ...) = 0;
        ThElementID GenElementID();
        void SetDrawArea(const ThRectf& area);
        const ThRectf& GetDrawArea()const;
        ThGuiElementPtr GetRootElement();
        const ThInput& GetInput()const;
        float GetDeltaTime()const;
        void Update();
        void Render();
		ThGuiElementPtr GetHotElement();
		void SetHotElement(ThGuiElementPtr elem);
		ThGuiElementPtr GetActiveElement();
		void SetActiveElement(ThGuiElementPtr elem);
		ThFontHandle GetDefaultFont()const;
		void SetDefaultFont(ThFontHandle font);
	protected:
        virtual void UpdateInputImpl() = 0;
        virtual void RenderImpl() = 0;
        
		ThInput m_Input;
		ThRectf m_DrawArea;
		ThGuiElementPtr m_Root;
		ThGuiElementPtr m_HotElement;
		ThGuiElementPtr m_LastHotElement;
		ThGuiElementPtr m_ActiveElement;
		ThGuiElementPtr m_LastActiveElement;
		ThElementID m_LastElementID;
		ThCommandBuffer m_RenderBuf;
		ThFontHandle m_DefaultFont;
        float m_DeltaTime;
	};
}