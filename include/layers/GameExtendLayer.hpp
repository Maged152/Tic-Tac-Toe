#pragma once
#include "Layer.hpp"
#include <string>

namespace qlm
{
   class GameExtendLayer : public Layer
	{
	private:
		Grid game_grid;
		Rectangle grid_loc;
		Font grid_font, text_font;
		int width, height;

		Location last_move;
		int max_x, min_x, max_y, min_y; // borders
		
	public:
		GameExtendLayer(const int width, const int height, const Font& grid_font, const Font& text_font, const Grid& grid, const Rectangle& grid_loc);
		virtual ~GameExtendLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender(const float ts) override;

	private:
		void DrawGrid();
	};

}