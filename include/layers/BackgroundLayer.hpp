#pragma once
#include "Layer.hpp"

namespace qlm
{
   class BackgroundLayer : public Layer
	{
		
	public:
		BackgroundLayer();
		virtual ~BackgroundLayer();
		virtual void OnUpdate() override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition() override;
	};
}