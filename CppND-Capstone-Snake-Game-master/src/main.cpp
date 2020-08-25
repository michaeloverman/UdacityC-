#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{128};
  constexpr std::size_t kGridHeight{64};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score Player 1: " << game.GetScore1() << "\n";
  std::cout << "          Size: " << game.GetSize() << "\n";
  std::cout << "Score Player 2: " << game.GetScore2() << "\n";
  std::cout << "          Size: " << game.GetSize() << "\n";
  return 0;
}