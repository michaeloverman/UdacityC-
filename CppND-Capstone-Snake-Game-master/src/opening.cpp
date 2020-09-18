#include "opening.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Opening::Opening() {
	// promise = _promise;
}

void OpeningScreen(Controller const &controller, Renderer &renderer) {
	// run opening screen until space bar click
	renderer.RenderStart(2);
	std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate wait for click
    // std::string modifiedMessage = message + " has been modified";
    // promise.set_value();
}
