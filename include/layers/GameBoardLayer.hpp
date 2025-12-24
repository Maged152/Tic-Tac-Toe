#pragma once
#include "Layer.hpp"
#include <limits>

namespace qlm
{
   class GameBoardLayer : public Layer
	{
	private:
		Grid& game_grid;

		Color hover_color = WHITE;
		Rectangle hover_cell;
		
	public:
		GameBoardLayer(const int width, const int height, const Font& font, Grid &grid);
		virtual ~GameBoardLayer();
		virtual void OnUpdate(GameContext& game_context) override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition(GameContext& game_context) override;

	private:
		void MakeMove(GameContext& game_context);
		void BestMove(GameContext& game_context);
		MoveEvaluation MiniMax(const Cell player, const Location player_move, const int cur_round, int best_for_x = std::numeric_limits<int>::min(),  int best_for_o = std::numeric_limits<int>::max());
		Cell Toggle(const Cell current);
		void IsGameOver(GameContext& game_context);
	};

}