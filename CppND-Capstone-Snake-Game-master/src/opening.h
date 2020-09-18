#ifndef OPENING_H
#define OPENING_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include <thread>
#include <future>
#include <iostream>

class Opening {
	public:
		Opening();
		void OpeningScreen(Controller const &controller, Renderer &renderer);
	private:
		std::promise<void> promise;
};

#endif