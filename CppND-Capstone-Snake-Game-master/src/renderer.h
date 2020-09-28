#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

	void RenderStart(int startMessagePos);
  void Render(Snake const snake1, Snake const snake2, SDL_Point const &food1, SDL_Point const &food2);
  void UpdateWindowTitle(int score1, int score2, int fps);

 private:
	void drawLetter(std::vector<std::pair<int, int>> l, int x, int y);
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // Letter and number definitions
  std::vector<std::pair<int, int>> letterp = { std::make_pair(0,0), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(2,3), std::make_pair(1,3) };
  std::vector<std::pair<int, int>> letterr = { std::make_pair(0,0), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(2,3), std::make_pair(1,3), std::make_pair(2,4), std::make_pair(3,5), std::make_pair(3,6) };
  std::vector<std::pair<int, int>> letterl = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(3,6) };
  std::vector<std::pair<int, int>> lettere = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(3,6), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0), std::make_pair(1,3), std::make_pair(2,3) };
  std::vector<std::pair<int, int>> letters = { std::make_pair(0,0), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(3,3), std::make_pair(3,4), std::make_pair(3,5), std::make_pair(2,3), std::make_pair(1,3), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(3,6) };
  std::vector<std::pair<int, int>> lettera = { std::make_pair(1,0), std::make_pair(2,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(2,3), std::make_pair(1,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(3,4), std::make_pair(3,5), std::make_pair(3,6) };
  std::vector<std::pair<int, int>> letterc = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(3,6), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0) };
  std::vector<std::pair<int, int>> lettert = { std::make_pair(1,0), std::make_pair(1,1), std::make_pair(1,2), std::make_pair(1,3), std::make_pair(1,4), std::make_pair(1,5), std::make_pair(1,6), std::make_pair(0,0), std::make_pair(2,0) };
  std::vector<std::pair<int, int>> letteri = { std::make_pair(1,1), std::make_pair(1,2), std::make_pair(1,3), std::make_pair(1,4), std::make_pair(1,5), std::make_pair(0,0), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(0,5), std::make_pair(2,5) };
  std::vector<std::pair<int, int>> lettero = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(3,4), std::make_pair(3,5), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(3,6), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,0) };
  std::vector<std::pair<int, int>> letterd = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(3,4), std::make_pair(3,5), std::make_pair(0,5), std::make_pair(0,6), std::make_pair(1,6), std::make_pair(2,6), std::make_pair(1,0), std::make_pair(2,0) };
  std::vector<std::pair<int, int>> letterk = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(3,0), std::make_pair(2,1), std::make_pair(1,2), std::make_pair(1,3), std::make_pair(2,4), std::make_pair(3,5) };
  std::vector<std::pair<int, int>> letterw = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3), std::make_pair(0,4), std::make_pair(0,5), std::make_pair(1,4), std::make_pair(2,3), std::make_pair(3,4), std::make_pair(4,5), std::make_pair(4,4), std::make_pair(4,3), std::make_pair(4,2), std::make_pair(4,1), std::make_pair(4,0) };
  std::vector<std::pair<int, int>> lettery = { std::make_pair(0,0), std::make_pair(1,1), std::make_pair(2,2), std::make_pair(4,0), std::make_pair(3,1), std::make_pair(2,3), std::make_pair(2,4), std::make_pair(2,5), std::make_pair(2,6) };
  std::vector<std::pair<int, int>> letterj = { std::make_pair(3,0), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(3,3), std::make_pair(3,4), std::make_pair(2,5), std::make_pair(1,5), std::make_pair(0,4)};
  std::vector<std::pair<int, int>> number1 = { std::make_pair(0,1), std::make_pair(1,1), std::make_pair(1,2), std::make_pair(1,3), std::make_pair(1,4), std::make_pair(1,5), std::make_pair(1,6), std::make_pair(0,6), std::make_pair(2,6) };
  std::vector<std::pair<int, int>> number2 = { std::make_pair(0,1), std::make_pair(1,0), std::make_pair(2,0), std::make_pair(3,1), std::make_pair(3,2), std::make_pair(2,3), std::make_pair(1,4), std::make_pair(0,5), std::make_pair(1,5), std::make_pair(2,5), std::make_pair(3,5) };
  std::vector<std::pair<int, int>> arrowUp = { std::make_pair(2,0), std::make_pair(2,1), std::make_pair(2,2), std::make_pair(2,3), std::make_pair(2,4), std::make_pair(2,5), std::make_pair(1,1), std::make_pair(3,1), std::make_pair(0,2), std::make_pair(4,2) };
  std::vector<std::pair<int, int>> arrowDown = { std::make_pair(2,0), std::make_pair(2,1), std::make_pair(2,2), std::make_pair(2,3), std::make_pair(2,4), std::make_pair(2,5), std::make_pair(1,4), std::make_pair(3,4), std::make_pair(0,3), std::make_pair(4,3) };
  std::vector<std::pair<int, int>> arrowRight = { std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2), std::make_pair(3,2), std::make_pair(4,2), std::make_pair(5,2), std::make_pair(4,1), std::make_pair(4,3), std::make_pair(3,0), std::make_pair(3,4) };
  std::vector<std::pair<int, int>> arrowLeft = { std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2), std::make_pair(3,2), std::make_pair(4,2), std::make_pair(5,2), std::make_pair(1,1), std::make_pair(1,3), std::make_pair(2,0), std::make_pair(2,4) };
  std::vector<std::vector<std::pair<int, int>>> startMessage = { letterp, letterr, lettere, letters, letters, letters, letterp, lettera, letterc, lettere, lettert, lettero, letterp, letterl, lettera, lettery };
  std::vector<int> startMessageSpacing = { 0, 6, 12, 18, 24, 34, 40, 46, 52, 58, 68, 73, 83, 89, 95, 101 };
  std::vector<std::vector<std::pair<int, int>>> playerOne = {letterp, number1, arrowUp, letterw, arrowLeft, lettera, arrowDown, letters, letterd, arrowRight };
  std::vector<int> playerOneHorz = { 2, 8, 18, 18, 4, 12, 18, 18, 24, 30 };
  std::vector<int> playerOneVert = { 12, 12, 12, 20, 28, 27, 35, 27, 27, 28 };
  std::vector<std::vector<std::pair<int, int>>> playerTwo = {letterp, number2, arrowUp, letteri, arrowLeft, letterj, arrowDown, letterk, letterl, arrowRight };
  std::vector<int> playerTwoHorz = { 85, 91, 72, 73, 58, 66, 72, 72, 78, 84 };
  std::vector<int> playerTwoVert = { 12, 12, 12, 20, 28, 27, 35, 27, 26, 28 };

};

#endif