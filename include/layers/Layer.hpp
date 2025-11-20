#pragma once
#include <raylib.h>
#include "types.hpp"

namespace qlm
{
   class Layer
	{
	private:
		Font font;
	public:
		virtual ~Layer() = default;
		virtual void OnUpdate(GameState& game_status) {}
		virtual void OnRender(const float ts) {}
	};

}