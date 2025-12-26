#include "layers/BackgroundLayer.hpp"
#include "TicTacToe.hpp"

qlm::BackgroundLayer::BackgroundLayer()
{}

qlm::BackgroundLayer::~BackgroundLayer()
{}

void qlm::BackgroundLayer::OnUpdate()
{}

void qlm::BackgroundLayer::OnRender(const float ts)
{
    ClearBackground(qlm::glb::back_ground);
    DrawTextEx(qlm::TicTacToe::game_context.font, "XO GAME", {qlm::TicTacToe::width / 2 - 200, 20}, 80, 10, qlm::glb::text_color);
}

void qlm::BackgroundLayer::OnTransition()
{}
