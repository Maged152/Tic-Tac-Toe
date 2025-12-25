#pragma once
#include <raylib.h>
#include "types.hpp"
#include <memory>
#include <concepts>

namespace qlm
{
   class Layer
	{
	public:
		virtual ~Layer() = default;
		Layer() {}
		virtual void OnUpdate() {}
		virtual void OnRender(const float ts) {}
		virtual void OnTransition() {}
		template<std::derived_from<Layer> T, typename... Args>
		std::unique_ptr<Layer> TransitionTo(Args&&... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}
	};

}