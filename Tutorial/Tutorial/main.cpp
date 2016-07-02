#include <SFML/Graphics.hpp>

#include "Game.h"

void main(int argc, char** argv[]) {
	// Program entry point.
	Game game; // Creating our game object.
	while (!game.GetWindow()->IsDone()) {
		// Game loop.
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
}
