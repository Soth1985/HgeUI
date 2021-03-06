#pragma once

#include "ThGuiForward.h"
#include "ThAnchors.h"
#include "ThCommandBuffer.h"
#include "ThDelegate.h"
#include <vector>

namespace Thor
{
    class ThGuiElement : public std::enable_shared_from_this<ThGuiElement>
    {
	private:
		typedef std::vector<ThGuiElementPtr> ChildrenContainer;
    public:
        ThGuiElement(ThGuiContext* context);
        virtual ~ThGuiElement();
        virtual void LayoutElementRecursive(const ThRectf& parentArea);
        virtual WidgetType GetType()const;
        
		ThGuiContext* GetContext();
        void RenderRecursive(ThCommandBuffer& cmd, uint16_t depth);
        bool PushChild(ThGuiElementPtr child);
        ThGuiElementPtr GetChild(ThElementID child);
        ThGuiElementPtr GetChildRecursive(ThElementID child);
        size_t GetNumChildren()const;
        ThGuiElementPtr GetChildByIndex(size_t index);
        ThGuiElementPtr GetChildByName(const std::string& name);
        ThGuiElementPtr GetChildByNameRecursive(const std::string& name);
        void GetChildrenByName(const std::string& name, ChildrenContainer& children);
        void GetChildrenByNameRecursive(const std::string& name, ChildrenContainer& children);
        bool SwapChildren(ThElementID c1, ThElementID c2);
        int32_t GetChildIndex(ThElementID c)const;
        ThGuiElement* GetParent();
        void SetParent(ThGuiElement* element);
        ThGuiElementPtr This();
        ThElementID GetElementID()const;
        const std::string& GetName()const;
        void SetName(const std::string& name);
        bool IsStateSet(int32_t state);
        void SetState(bool enable, int32_t state);
        void SetStateRecursive(bool enable, int32_t state);
        const ThDim2& GetPosition()const;
        void SetPosition(const ThDim2& pos);
        ThDim2 GetSize()const;
        void SetSize(const ThDim2& pos);
        const ThColor& GetColor()const;
        void SetColor(const ThColor& color);
        ThTexHandle GetTexture()const;
        void SetTexture(ThTexHandle texture, const ThColor& overrideColor = WhiteColor);
		const ThColor& GetBorderColor()const;
		void SetBorderColor(const ThColor& color);
		float GetBorderWidth()const;
		void SetBorderWidth(float width);
		uint16_t GetLayer()const;
		void SetLayer(uint16_t layer);
        void SetLayerRecursive(uint16_t layer);
        const ThRectf& GetRealRect()const;
        float GetAspectRatioConstraint()const;
        void SetAspectRatioConstraint(float aspect);
		bool SetAnchor(Anchor point, ThGuiElementPtr target, Anchor targetPoint, const ThDim2& offset = EmptyDim2);
		void ClearAnchors();
        
        typedef ThDelegate<ThGuiElement*, const ThVec2f&> OnMouseMoveDel;
        typedef ThDelegate<ThGuiElement*, const ThVec2f&> OnMouseEnterDel;
        typedef ThDelegate<ThGuiElement*, const ThVec2f&> OnMouseLeaveDel;
        typedef ThDelegate<ThGuiElement*, MouseButton> OnMouseButtonPressedDel;
        typedef ThDelegate<ThGuiElement*, MouseButton> OnMouseButtonReleasedDel;
        
        OnMouseMoveDel md_OnMouseMove;
        OnMouseEnterDel md_OnMouseEnter;
        OnMouseLeaveDel md_OnMouseLeave;
        OnMouseButtonPressedDel md_OnMouseButtonPressed;
        OnMouseButtonReleasedDel md_OnMouseButtonReleased;
    protected:
        virtual void ProcessInput();
        virtual bool IsClipper();
        virtual void RenderElement(ThCommandBuffer& cmd, uint16_t depth);
		virtual void LayoutElement(const ThRectf& parentArea);
        
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
        float m_AspectRatioConstraint;
		ThAnchors m_Anchors;
    };
}