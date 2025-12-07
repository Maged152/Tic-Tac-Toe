#pragma once
#include "Layer.hpp"
#include <string>

namespace qlm
{
   class GameExtendLayer : public Layer
	{
	private:
		Grid& game_grid;
		Font text_font;
		int width, height;

		bool moved = false, shifted = false;

		Direction extend_direction;
		
	public:
		GameExtendLayer(const int width, const int height, const Font& text_font, Grid& grid);
		virtual ~GameExtendLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender(const float ts) override;

	private:
		void RemoveMoves(const Direction dir);
		void ShiftGrid(const Direction dir);
	};

}