#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake1(grid_width, grid_height, 1), snake2(grid_width, grid_height, 2),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)), // Added '-1'. This was a bug: If it chose max of grid_width, it was "off screen" and never edible
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood(food1);
  PlaceFood(food2);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake1);
    controller.HandleInput(running, snake2);
    Update();
    renderer.Render(snake1, snake2, food1, food2);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood(SDL_Point &food) {
	// std::cout << "PlaceFood()" << std::endl;
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
	// std::cout << "Loc, x: " << x << ", y: " << y << std::endl;
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake1.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
	// std::cout << "Food part of snake, trying again..." << std::endl;
  }
}

void Game::Update() {
  if (!snake1.alive) return;

  snake1.Update();
  snake2.Update();

  int new_x = static_cast<int>(snake1.head_x);
  int new_y = static_cast<int>(snake1.head_y);

  // Check if there's food over here
  if (food1.x == new_x && food1.y == new_y) {
    score++;
    PlaceFood(food1);
    // Grow snake and increase speed.
    snake1.GrowBody();
    snake1.speed += 0.02;
  }
  if (food2.x == new_x && food2.y == new_y) {
    score++;
    PlaceFood(food2);
    // Grow snake and increase speed.
    snake1.GrowBody();
    snake1.speed += 0.02;
  }
  new_x = static_cast<int>(snake2.head_x);
  new_y = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  if (food1.x == new_x && food1.y == new_y) {
    score++;
    PlaceFood(food1);
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
  }
  if (food2.x == new_x && food2.y == new_y) {
    score++;
    PlaceFood(food2);
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake1.size; }