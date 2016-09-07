#pragma once

#include "ThGui.h"

namespace Thor
{
	class ThGuiContextHge : public ThGuiContext
	{
	public:

	protected:
		virtual void UpdateInputImpl()override;
		virtual void RenderImpl()override;
	};
}