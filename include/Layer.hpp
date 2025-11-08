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
		virtual void OnUpdate(float ts) {}
		virtual Status OnRender() {}
	};

}