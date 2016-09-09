#pragma once

#include "ThGuiForward.h"
#include "ThCommandBuffer.h"
#include "ThDelegate.h"
#include <vector>

namespace Thor
{
    class ThGuiElement : std::enable_shared_from_this<ThGuiElement>
    {
	private:
		typedef std::vector<ThGuiElementPtr> ChildrenContainer;
    public:
        ThGuiElement(ThGuiContext* context);
        virtual ~ThGuiElement();
        virtual void LayoutRecursive(const ThRectf& parentArea);
        virtual void ProcessInputRecursive();
        virtual WidgetType GetType()const;
        
        void RenderRecursive(ThCommandBuffer& cmd, uint16_t depth);
        bool PushChild(ThGuiElementPtr child);
        ThGuiElementPtr GetChild(ThElementID child);
        ThGuiElementPtr GetChildRecursive(ThElementID child);
        size_t GetNumChildren()const;
        ThGuiElementPtr GetChildByIndex(size_t index);
        void GetChildrenByName(const std::string& name, ChildrenContainer& children);
        void GetChildrenByNameRecursive(const std::string& name, ChildrenContainer& children);
        bool SwapChilds(ThElementID c1, ThElementID c2);
        int32_t GetChildIndex(ThElementID c)const;
        ThGuiElement* GetParent();
        void SetParent(ThGuiElement* element);
        ThGuiElementPtr This();
        ThElementID GetElementID()const;
        const std::string& GetName()const;
        void SetName(const std::string& name);
        bool IsStateSet(uint32_t state);
        void SetState(bool enable, uint32_t state);
        void SetStateRecursive(bool enable, uint32_t state);
        const ThDim2& GetPosition()const;
        void SetPosition(const ThDim2& pos);
        ThDim2 GetSize()const;
        void SetSize(const ThDim2& pos);
        const ThColor& GetColor()const;
        void SetColor(ThColor& color);
        ThTexHandle GetTexture()const;
        void SetTexture(ThTexHandle texture);
		const ThColor& GetBorderColor()const;
		void SetBorderColor(const ThColor& color);
		uint16_t GetLayer()const;
		void SetLayer(uint16_t layer);
        
        typedef ThDelegate<ThGuiElement*, float, float> OnMouseMoveDel;
        typedef ThDelegate<ThGuiElement*, float, float> OnMouseEnterDel;
        typedef ThDelegate<ThGuiElement*, float, float> OnMouseLeaveDel;
        typedef ThDelegate<ThGuiElement*, MouseButton> OnMouseButtonPressedDel;
        typedef ThDelegate<ThGuiElement*, MouseButton> OnMouseButtonReleasedDel;
        
        OnMouseMoveDel md_OnMouseMove;
        OnMouseEnterDel md_OnMouseEnter;
        OnMouseLeaveDel md_OnMouseLeave;
        OnMouseButtonPressedDel md_OnMouseButtonPressed;
        OnMouseButtonReleasedDel md_OnMouseButtonReleased;
    protected:
        virtual void RenderElement(ThCommandBuffer& cmd, uint16_t depth);
        
        ThGuiElement* m_Parent;
        ThGuiContext* m_Context;
        ChildrenContainer m_Children;
        ThElementID m_ID;
        std::string m_Name;
        ThFlags32 m_State;
        ThDimRect m_LayoutRect;
        ThRectf m_RealRect;
        ThColor m_Color;
        ThTexHandle m_Texture;
        ThColor m_BorderColor;
		uint16_t m_Layer;
        float m_BorderWidth;
    };
}