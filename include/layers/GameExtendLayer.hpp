#pragma once
#include "Layer.hpp"
#include <string>

namespace qlm
{
   class GameExtendLayer : public Layer
	{
	private:
		Grid& game_grid;
		int width, height;

		bool moved = false, shifted = false;

		Direction extend_direction;
		
	public:
		GameExtendLayer(const int width, const int height, const Font& text_font, Grid& grid);
		virtual ~GameExtendLayer();
		virtual void OnUpdate(GameContext& game_context) override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition(GameContext& game_context) override;

	private:
		void RemoveMoves(const Direction dir);
		void ShiftGrid(const Direction dir);
	};

}