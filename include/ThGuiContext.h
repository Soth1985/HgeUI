#pragma once

#include "ThGuiForward.h"
#include "ThInput.h"

namespace Thor
{
	class ThGuiContext : std::enable_shared_from_this<ThGuiContext>
	{
	public:
        ThGuiContext();
		virtual ~ThGuiContext();
		virtual ThTexHandle CreateTexture(const std::string& name) = 0;
        virtual bool Init() = 0;
        virtual void ShutDown() = 0;
        virtual void Log(const char* format, ...) = 0;
        ThElementID GenElementID();
        void SetDrawArea(const ThRectf& area);
        const ThRectf& GetDrawArea()const;
        ThGuiElementPtr GetRootElement();
        const ThInput& GetInput()const;
        float GetDeltaTime()const;
        void Update();
        void Render();
	protected:
        virtual void UpdateInputImpl() = 0;
        virtual void RenderImpl() = 0;
        
		ThInput m_Input;
		ThRectf m_DrawArea;
		ThGuiElementPtr m_Root;
		ThElementID m_LastElementID;
        float m_DeltaTime;
	};
}