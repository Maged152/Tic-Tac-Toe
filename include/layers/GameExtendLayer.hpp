#pragma once
#include "Layer.hpp"
#include <string>

namespace qlm
{
   class GameExtendLayer : public Layer
	{
	private:
		bool moved = false, shifted = false;
		Direction extend_direction;
		
	public:
		GameExtendLayer();
		virtual ~GameExtendLayer();
		virtual void OnUpdate() override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition() override;

	private:
		void RemoveMoves(const Direction dir);
		void ShiftGrid(const Direction dir);
	};

}