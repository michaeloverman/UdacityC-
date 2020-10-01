#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>
// #include <promise>
// #include <future>

Game::Game(std::size_t grid_width, std::size_t grid_height)
		: snake1(grid_width, grid_height, 1), snake2(grid_width, grid_height, 2),
		engine(dev()),
		random_w(0, static_cast<int>(grid_width-1)), // Added '-1'. This was a bug: If it chose max of grid_width, it was "off screen" and never edible
		random_h(0, static_cast<int>(grid_height-1)) {
	PlaceFood(food1);
	PlaceFood(food2);
}

void Game::OpeningScreen(std::promise<void> &&promise, Controller const &controller, Renderer &renderer) {
	// run opening screen until space bar click
	std::cout << "OpeningScreen()" << std::endl;

	bool running = true;
	Uint32 count = 0;

	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int messagePos = 2;
	bool messageRight = true;

	while (running) {
		frame_start = SDL_GetTicks();

		controller.HandleInput(running);

		count++;
		renderer.RenderStart(messagePos);

		if (count % 2 == 0) {
			if (messageRight) messagePos++;
			else messagePos--;
			if (messagePos == 30) messageRight = false;
			if (messagePos == -6 ) messageRight = true;
		}

		frame_end = SDL_GetTicks();

		frame_duration = frame_end - frame_start;

		if (frame_end - title_timestamp >= 1000) {
			renderer.UpdateWindowTitle(0, 0, count);
			count = 0;
			title_timestamp = frame_end;
		}

		if (frame_duration < 1000 / 60) {
			SDL_Delay(1000/60 - frame_duration);
		}
	}
	std::cout << "Setting value on promise to return to..." << std::endl;
    promise.set_value();
}

void Game::Run(Controller const &controller, Renderer &renderer,
			 std::size_t target_frame_duration) {
	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int frame_count = 0;
	bool running = true;
	startMessagePos = 2;

    // create promise and future
    std::promise<void> prms;
    std::future<void> ftr = prms.get_future();

    // start thread and pass promise as argument
    OpeningScreen(std::move(prms), controller, renderer);

    // retrieve modified message via future and print to console
	try {
		ftr.wait();
		std::cout << "Returned from opening screen promise/future" << std::endl;
	} catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}

	while (running) {
		frame_start = SDL_GetTicks();

		// Input, Update, Render - the main game loop.
		controller.HandleInput(running, snake1, snake2);
		Update();
		// startMessagePos++;
		renderer.Render(snake1, snake2, food1, food2);
		// renderer.RenderStart(startMessagePos);

		frame_end = SDL_GetTicks();

		// Keep track of how long each loop through the input/update/render cycle
		// takes.
		frame_count++;
		frame_duration = frame_end - frame_start;

		// After every second, update the window title.
		if (frame_end - title_timestamp >= 1000) {
			renderer.UpdateWindowTitle(GetScore1(), GetScore2(), frame_count);
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
		if (!snake1.SnakeCell(x, y, true) && !snake2.SnakeCell(x, y, true)) {
			food.x = x;
			food.y = y;
			return;
		}
		// std::cout << "Food part of snake, trying again..." << std::endl;
	}
}

void Game::Update() {
	if (!snake1.alive || !snake2.alive) return;

	snake1.Update();
	snake2.Update();

	// Check if either snake has run into itself or the other
	if (snake1.SnakeCell(snake1.head_x, snake1.head_y, false) || snake2.SnakeCell(snake1.head_x, snake1.head_y, true)) {
		// snake 1 is dead
		snake1.alive = false;
	}
	if (snake1.SnakeCell(snake2.head_x, snake2.head_y, true) || snake2.SnakeCell(snake2.head_x, snake2.head_y, false)) {
		// snake 2 is dead
		snake2.alive = false;
	}

	int new_x = static_cast<int>(snake1.head_x);
	int new_y = static_cast<int>(snake1.head_y);

	// Check if there's food over here
	if (food1.x == new_x && food1.y == new_y) {
		snake1.IncScore();
		PlaceFood(food1);
		// Grow snake and increase speed.
		snake1.GrowBody();
		snake1.speed += 0.01;
	}
	if (food2.x == new_x && food2.y == new_y) {
		snake1.IncScore();
		PlaceFood(food2);
		// Grow snake and increase speed.
		snake1.GrowBody();
		snake1.speed += 0.01;
	}
	new_x = static_cast<int>(snake2.head_x);
	new_y = static_cast<int>(snake2.head_y);

	// Check if there's food over here
	if (food1.x == new_x && food1.y == new_y) {
		snake2.IncScore();
		PlaceFood(food1);
		// Grow snake and increase speed.
		snake2.GrowBody();
		snake2.speed += 0.01;
	}
	if (food2.x == new_x && food2.y == new_y) {
		snake2.IncScore();
		PlaceFood(food2);
		// Grow snake and increase speed.
		snake2.GrowBody();
		snake2.speed += 0.01;
	}
}

int Game::GetScore1() const { return snake1.score; }
int Game::GetScore2() const { return snake2.score; }
int Game::GetSize1() const { return snake1.size; }
int Game::GetSize2() const { return snake2.size; }