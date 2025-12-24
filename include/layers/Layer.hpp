#pragma once
#include <raylib.h>
#include "types.hpp"
#include <memory>
#include <concepts>

namespace qlm
{
   class Layer
	{
	protected:
		Font font;

	public:
		virtual ~Layer() = default;
		Layer(const Font& f) : font(f) {}
		Layer() {}
		virtual void OnUpdate(GameContext& game_context) {}
		virtual void OnRender(const float ts) {}
		virtual void OnTransition(GameContext& game_context) {}
		template<std::derived_from<Layer> T, typename... Args>
		std::unique_ptr<Layer> TransitionTo(Args&&... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}
	};

}