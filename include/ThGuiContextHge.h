#pragma once

#include "ThGui.h"
#include "hge.h"
#include <unordered_map>

class hgeFont;

namespace Thor
{
	class ThGuiContextHge : public ThGuiContext
	{
	public:
        ThGuiContextHge(HGE* hge);
        virtual ThTexHandle CreateTexture(const std::string& name)override;
        virtual bool Init()override;
        virtual void Shutdown()override;
        virtual void Log(const char* format, ...)override;
        virtual ThFontHandle CreateTextFont(const std::string& name)override;
        virtual float GetFontHeight(ThFontHandle font)override;
        virtual float GetStringWidth(ThFontHandle font, const std::string& text)override;
	protected:
		virtual void UpdateInputImpl()override;
		virtual void RenderImpl()override;
        
        typedef std::unordered_map<std::string, HTEXTURE> TexturesMap;
        typedef std::unordered_map<std::string, hgeFont*> FontsMap;
        
        HGE* m_Hge;
        TexturesMap m_Textures;
        FontsMap m_Fonts;
	};
}