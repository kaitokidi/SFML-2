#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	sf::Time GetElapsed();
	void RestartClock();

	Window* GetWindow();
private:
	Window window;
	sf::Clock clock;
	float elapsed;

	World world;
	Snake snake;
	Textbox textbox;
};