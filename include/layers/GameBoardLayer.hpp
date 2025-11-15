#pragma once
#include "Layer.hpp"
#include <limits>

namespace qlm
{
   class GameBoardLayer : public Layer
	{
	public:
		Grid game_grid;
		Rectangle grid_loc;
		
	private:
		static const int cells = 9;
        static const int cell_size = 150;

		Font grid_font;

		Location last_move;

		Color hover_color = WHITE;
		Rectangle hover_cell;

		int round = 0;
		Cell turn = Cell::X;
		
	public:
		GameBoardLayer(const int width, const int height, const Font &font);
		virtual ~GameBoardLayer();
		virtual void OnUpdate(GameState& game_status) override;
		virtual void OnRender() override;

	private:
		void DrawGrid();
		void MakeMove(GameState& game_status);
		void BestMove(GameState& game_status);
		MoveEvaluation MiniMax(const Cell player, const Location player_move, const int cur_round, int best_for_x = std::numeric_limits<int>::min(),  int best_for_o = std::numeric_limits<int>::max());
		Cell Toggle(const Cell current);
		void IsGameOver(GameState& game_status);
	};

}