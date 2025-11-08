#pragma once
#include "Layer.hpp"

namespace qlm
{
   class MainMenuLayer : public Layer
	{
	private:
		// Define button dimensions and positions
		static const int button_width = 320;
		static const int button_height = 90;

		Rectangle start_button, exit_button;
		Color draw_color;
		
	public:
		MainMenuLayer(const Font& font);
		virtual ~MainMenuLayer();
		virtual void OnUpdate(float ts) override;
		virtual Status OnRender() override;

	private:
		void DrawButton(const Rectangle& button, const char* text, const Color text_color);
	};

}