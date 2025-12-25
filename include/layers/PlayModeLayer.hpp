#pragma once
#include "Layer.hpp"

namespace qlm
{
   class PlayModeLayer : public Layer
	{
	private:
		// Define button dimensions and positions
		static const int button_width = 600;
		static const int button_height = 110;

		Rectangle single_button, multi_button;
		Color single_color, multi_color;
				
	public:
		PlayModeLayer();
		virtual ~PlayModeLayer();
		virtual void OnUpdate() override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition() override;

	private:
		void DrawButton(const Rectangle& button, const Color button_color, const char* text, const int displacement);
	};

}