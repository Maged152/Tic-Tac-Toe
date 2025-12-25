#pragma once
#include "Layer.hpp"

namespace qlm
{
   class PieceSelectionLayer : public Layer
	{
	private:
		// Define button dimensions and positions
		static const int button_width = 320;
		static const int button_height = 90;

		Rectangle x_button, o_button;
		Color x_color, o_color;
		
	public:
		PieceSelectionLayer(const int width, const int height, const Font& font);
		virtual ~PieceSelectionLayer();
		virtual void OnUpdate() override;
		virtual void OnRender(const float ts) override;
		virtual void OnTransition() override;

	private:
		void DrawButton(const Rectangle& button, const Color button_color, const char* text, const Color text_color);
	};

}