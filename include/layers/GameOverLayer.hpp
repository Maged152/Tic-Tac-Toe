#pragma once
#include "Layer.hpp"
#include <string>

namespace qlm
{
   class GameOverLayer : public Layer
	{
	private:
		// Define button dimensions and positions
		static const int button_width = 350;
		static const int button_height = 80;

		Rectangle replay_button, main_button;
		Color replay_color, main_color;
		std::string result_text = "";

		const Grid& game_grid;

		Font text_font;
		int width, height;
		
	public:
		GameOverLayer(const int width, const int height, const Font& text_font, const Grid& grid);
		virtual ~GameOverLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender(const float ts) override;

	private:
		void DrawButton(const Rectangle& button, const Color button_color, const char* text, const Color text_color);
	};

}