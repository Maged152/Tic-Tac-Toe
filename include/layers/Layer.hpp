#pragma once
#include <raylib.h>
#include "types.hpp"
#include <memory>
#include <concepts>

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
		virtual void OnTransition(GameState& game_status) {}
		template<std::derived_from<Layer> T, typename... Args>
		std::unique_ptr<Layer> TransitionTo(Args&&... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}
	};

}