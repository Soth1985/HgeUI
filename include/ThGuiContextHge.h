#pragma once

#include "ThGui.h"
#include "hge.h"
#include <unordered_map>

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
	protected:
		virtual void UpdateInputImpl()override;
		virtual void RenderImpl()override;
        
        typedef std::unordered_map<std::string, HTEXTURE> TexturesMap;
        
        HGE* m_Hge;
        TexturesMap m_Textures;
	};
}