#pragma once

#include "ThGuiContext.h"

namespace Thor
{
	class ThGuiContextHge : public ThGuiContext
	{
	protected:
		virtual void UpdateInputImpl()override;
		virtual void RenderImpl()override;
	};
}