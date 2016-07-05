#ifndef SNAKE_H
#define SNAKE_H

#include <SFML\Graphics.hpp>

#include "Window.h"
#include "Textbox.h"

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

enum class Direction { None, Up, Down, Left, Right };

using SnakeContainer = std::vector<SnakeSegment>;

class Snake {
public:
	Snake(int blockSize, Textbox& textbox);
	~Snake();

	// Helper methods.
	void SetDirection(Direction dir);
	Direction GetDirection() const;
	Direction GetPhyiscalDirection() const;
	int GetSpeed() const;
	sf::Vector2i GetPosition() const;
	int GetLives() const;
	int GetScore() const;
	void IncreaseScore();
	bool HasLost() const;

	void Lose(); // Handle losing here.
	void ToggleLost();

	void Extend(); // Grow the snake.
	void Reset(); // Reset to starting position.

	void Move(); // Movement method.
	void Tick(); // Update method.
	void Cut(int segments); // Method for cutting snake.
	void Render(Window& window);

private:
	void CheckCollision(); // Checking for collisions.

	SnakeContainer snakeBody; // Segment vector.
	int size;
	Direction dir;
	int speed;
	int lives;
	int score;
	bool lost;
	sf::RectangleShape bodyRect;
	Textbox& textbox;
};



#endif