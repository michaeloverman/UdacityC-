#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
									 const std::size_t screen_height,
									 const std::size_t grid_width, const std::size_t grid_height)
		: screen_width(screen_width),
			screen_height(screen_height),
			grid_width(grid_width),
			grid_height(grid_height) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}

// std::cout << "Creating window..." << std::endl;
	// Create Window
	sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
																SDL_WINDOWPOS_CENTERED, screen_width,
																screen_height, SDL_WINDOW_SHOWN);

	if (nullptr == sdl_window) {
		std::cerr << "Window could not be created.\n";
		std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
	}

// std::cout << "Creating renderer..." << std::endl;
	// Create renderer
	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == sdl_renderer) {
		std::cerr << "Renderer could not be created.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}

  // letterp[] = { std::make_pair(0,0), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(2,3), std::make_pair(1,3) };
}

Renderer::~Renderer() {
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Renderer::drawLetter(std::vector<std::pair<int, int>> l, int x, int y) {
	SDL_Rect block;
	block.w = screen_width / grid_width;
	block.h = screen_height / grid_height;

	for (auto p : l) {
		block.x = (x + p.first) * block.w;
		block.y = (y + p.second) * block.h;
		SDL_RenderFillRect(sdl_renderer, &block);
	}
}

void Renderer::RenderStart(int messageStartPos) {
	SDL_Rect block;
	block.w = screen_width / grid_width;
	block.h = screen_height / grid_height;

	// Clear screen
	SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(sdl_renderer);

	// Render Message
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for (int i = 0; i < startMessage.size(); i++) {
		Renderer::drawLetter(startMessage[i], messageStartPos + startMessageSpacing[i], 2);
	}

	// Update Screen
	SDL_RenderPresent(sdl_renderer);
	std::cout << "SDL_RenderPresent called - there should be a screen?!" << std::endl;
}

void Renderer::Render(Snake const snake1, Snake const snake2, SDL_Point const &food1, SDL_Point const &food2) {
	SDL_Rect block;
	block.w = screen_width / grid_width;
	block.h = screen_height / grid_height;

	// Clear screen
	SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(sdl_renderer);

	// Render food
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
	block.x = food1.x * block.w;
	block.y = food1.y * block.h;
	SDL_RenderFillRect(sdl_renderer, &block);
	block.x = food2.x * block.w;
	block.y = food2.y * block.h;
	SDL_RenderFillRect(sdl_renderer, &block);

	// Render snake's body
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xAA, 0xFF, 0xFF);
	for (SDL_Point const &point : snake1.body) {
		block.x = point.x * block.w;
		block.y = point.y * block.h;
		SDL_RenderFillRect(sdl_renderer, &block);
	}

	// Render snake's head
	block.x = static_cast<int>(snake1.head_x) * block.w;
	block.y = static_cast<int>(snake1.head_y) * block.h;
	if (snake1.alive) {
		SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
	} else {
		SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
	}
	SDL_RenderFillRect(sdl_renderer, &block);

	// Render snake's body
	SDL_SetRenderDrawColor(sdl_renderer, 0xAA, 0xFF, 0xFF, 0xFF);
	for (SDL_Point const &point : snake2.body) {
		block.x = point.x * block.w;
		block.y = point.y * block.h;
		SDL_RenderFillRect(sdl_renderer, &block);
	}

	// Render snake's head
	block.x = static_cast<int>(snake2.head_x) * block.w;
	block.y = static_cast<int>(snake2.head_y) * block.h;
	if (snake2.alive) {
		SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
	} else {
		SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
	}
	SDL_RenderFillRect(sdl_renderer, &block);

	// Update Screen
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score1, int score2, int fps) {
	std::string title{"Player 1: " + std::to_string(score1) + "  --  Player 2: " + std::to_string(score2) + "  --  FPS: " + std::to_string(fps)};
	SDL_SetWindowTitle(sdl_window, title.c_str());
}
