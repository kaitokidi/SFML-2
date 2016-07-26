#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Window.h"

class World{
public:
	World(sf::Vector2u windSize);
	~World();

	int GetBlockSize();

	void RespawnApple();

	void Update(Snake& player);
	void Render(Window& window);
private:
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int blockSize;

	sf::CircleShape appleShape;
	sf::RectangleShape bounds[4];
};