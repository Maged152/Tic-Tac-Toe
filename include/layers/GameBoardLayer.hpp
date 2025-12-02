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

		int round = 0;
		Cell turn = Cell::X;
		
	public:
		GameBoardLayer(const int width, const int height, Grid &grid);
		virtual ~GameBoardLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender(const float ts) override;

	private:
		void MakeMove(GameState& game_status);
		void BestMove(GameState& game_status);
		MoveEvaluation MiniMax(const Cell player, const Location player_move, const int cur_round, int best_for_x = std::numeric_limits<int>::min(),  int best_for_o = std::numeric_limits<int>::max());
		Cell Toggle(const Cell current);
		void IsGameOver(GameState& game_status);
	};

}