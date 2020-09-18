#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <thread>
#include <future>
#include <iostream>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore1() const;
  int GetScore2() const;
  int GetSize1() const;
  int GetSize2() const;

 private:
  Snake snake1;
  Snake snake2;
  SDL_Point food1;
  SDL_Point food2;
  int startMessagePos;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

//   int score{0};
  static void OpeningScreen(std::promise<void> && prms, Controller const &controller, Renderer &renderer);
  void PlaceFood(SDL_Point &food);
  void Update();
};

#endif