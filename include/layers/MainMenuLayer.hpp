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
		Color start_color, exit_color;
		Font font;
		
	public:
		MainMenuLayer(const int width, const int height, const Font& font);
		virtual ~MainMenuLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender() override;

	private:
		void DrawButton(const Rectangle& button, const Color button_color, const char* text, const Color text_color, const int displacement);
	};

}