#include <SFML\Graphics.hpp>

#include <iostream>

#include "Snake.h"
#include "Window.h"

Snake::Snake(int blockSize, Textbox& textbox) :
	size(blockSize), textbox(textbox) {
	bodyRect.setSize(sf::Vector2f(size - 0, size - 0));
	Reset();
}

Snake::~Snake() {}

void Snake::SetDirection(Direction dir) {
	this->dir = dir;
}

Direction Snake::GetDirection() const {
	return dir;
}

Direction Snake::GetPhyiscalDirection() const {
	if (snakeBody.size() <= 1) {
		return Direction::None;
	}

	const SnakeSegment& head = snakeBody[0];
	const SnakeSegment& neck = snakeBody[1];

	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y) ?
			Direction::Down :
			Direction::Up;
	} else {
		return (head.position.x > neck.position.x) ?
			Direction::Right :
			Direction::Left;
	}
}

int Snake::GetSpeed() const {
	return speed;
}

sf::Vector2i Snake::GetPosition() const {
	return !snakeBody.empty()
		? snakeBody.front().position
		: sf::Vector2i(1, 1);
}

int Snake::GetLives() const {
	return lives;
}

int Snake::GetScore() const {
	return score;
}

void Snake::IncreaseScore() {
	score += 10;
	textbox.Add("You ate an apple! Score: " + std::to_string(score));
}

bool Snake::HasLost() const {
	return lost;
}

void Snake::Lose() {
	lost = true;
	textbox.Clear();
	textbox.Add("");
	textbox.Add("");
	textbox.Add("");
	textbox.Add("");
	textbox.Add("Game Over! Score: " + std::to_string(score));
}

void Snake::ToggleLost() {
	lost = !lost;
}

void Snake::Extend() {
	if (snakeBody.empty()) {
		return;
	}

	speed += 1;

	SnakeSegment& tail_head = snakeBody[snakeBody.size() - 1];

	if (snakeBody.size() > 1) {
		SnakeSegment& tail_bone = snakeBody[snakeBody.size() - 2];

		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				snakeBody.push_back(SnakeSegment(tail_head.position.x,
					tail_head.position.y + 1));
			}
			else {
				snakeBody.push_back(SnakeSegment(tail_head.position.x,
					tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				snakeBody.push_back(SnakeSegment(tail_head.position.x + 1,
					tail_head.position.y));
			}
			else {
				snakeBody.push_back(SnakeSegment(tail_head.position.x - 1,
					tail_head.position.y));
			}
		}
	}
	else {
		if (dir == Direction::Up) {
			snakeBody.push_back(SnakeSegment(tail_head.position.x,
				tail_head.position.y + 1));
		}
		else if (dir == Direction::Down) {
			snakeBody.push_back(SnakeSegment(tail_head.position.x,
				tail_head.position.y - 1));
		}
		else if (dir == Direction::Left) {
			snakeBody.push_back(SnakeSegment(tail_head.position.x + 1,
				tail_head.position.y));
		}
		else if (dir == Direction::Right) {
			snakeBody.push_back(SnakeSegment(tail_head.position.x - 1,
				tail_head.position.y));
		}
	}
}

void Snake::Reset() {
	snakeBody.clear();

	snakeBody.push_back(SnakeSegment(5, 5));
	snakeBody.push_back(SnakeSegment(5, 4));
	snakeBody.push_back(SnakeSegment(5, 3));

	SetDirection(Direction::None); // start off still.
	speed = 10;
	lives = 3;
	score = 0;
	lost = false;
}


void Snake::Move() {
	for (int i = snakeBody.size() - 1; i > 0; --i) {
		snakeBody[i].position = snakeBody[i - 1].position;
	}
	if (dir == Direction::Left) {
		--snakeBody[0].position.x;
	}
	else if (dir == Direction::Right) {
		++snakeBody[0].position.x;
	}
	else if (dir == Direction::Up) {
		--snakeBody[0].position.y;
	}
	else if (dir == Direction::Down) {
		++snakeBody[0].position.y;
	}
}

void Snake::Tick() {
	if (snakeBody.empty()) {
		return;
	}
	if (dir == Direction::None) {
		return;
	}
	Move();
	CheckCollision();
}

void Snake::Cut(int segments) {
	textbox.Add("You ran into yourself and lost " +
		std::to_string(segments) + " segments");
	for (int i = 0; i != segments; ++i) {
		snakeBody.pop_back();
	}
	--lives;
	std::cout << lives << "\n";
	if (!lives) {
		Lose();
	}
}

void Snake::Render(Window& window) {
	if (snakeBody.empty()) {
		return;
	}

	auto head = snakeBody.begin();
	bodyRect.setFillColor(sf::Color::Yellow);
	bodyRect.setPosition(head->position.x * size,
		head->position.y * size);
	window.Draw(bodyRect);

	bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = snakeBody.begin() + 1;
		itr != snakeBody.end(); ++itr)
	{
		bodyRect.setPosition(itr->position.x * size,
			itr->position.y * size);
		if (itr + 1 == snakeBody.end()) {
			bodyRect.setFillColor(sf::Color::White);
		}
		window.Draw(bodyRect);
	}
}

void Snake::CheckCollision() {
	if (snakeBody.size() < 5) { return; }
	SnakeSegment& head = snakeBody.front();
	for (auto itr = snakeBody.begin() + 1;
		itr != snakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int segments = snakeBody.end() - itr;
			Cut(segments);
			break;
		}
	}
}
