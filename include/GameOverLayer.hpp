#pragma once
#include "Layer.hpp"

namespace qlm
{
   class GameOverLayer : public Layer
	{
	private:
		// Define button dimensions and positions
		static const int button_width = 350;
		static const int button_height = 80;

		Rectangle replay_button, main_button;
		Color draw_color;
		Font font;
		std::string result_text = "";
		Cell winner = Cell::EMPTY;
		
	public:
		GameOverLayer(const int width, const int height, const Font& font);
		virtual ~GameOverLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender() override;

	private:
		void DrawButton(const Rectangle& button, const char* text, const Color text_color);
	};

}