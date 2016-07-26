#include <SFML\Graphics.hpp>

#include <iostream>

#include "Snake.h"
#include "Window.h"

Snake::Snake(int blockSize, Textbox& textbox) :
	size(blockSize), textbox(textbox) {
	music.openFromFile("Electrix_NES.ogg");
	music.setLoop(true);
	music.play();
	loseSoundBuffer.loadFromFile("footstep.ogg");
	loseSound.setBuffer(loseSoundBuffer);
	eatSoundBuffer.loadFromFile("glass.ogg");
	eatSound.setBuffer(eatSoundBuffer);
	bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
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
	eatSound.play();
	score += 10;
	textbox.Add("You ate an apple! Score: " + std::to_string(score));
}

bool Snake::HasLost() const {
	return lost;
}

void Snake::Lose() {
	music.pause();
	lost = true;
	textbox.Clear();
	textbox.Add("");
	textbox.Add("");
	textbox.Add("");
	textbox.Add("");
	textbox.Add("Game Over! Score: " + std::to_string(score));
	for (int i = 0; i != 4; ++i) {
		loseSound.play();
		sf::sleep(sf::milliseconds(200));
	}
	music.play();
}

void Snake::ToggleLost() {
	lost = !lost;
}

void Snake::Extend() {
	if (snakeBody.empty()) {
		return;
	}

	speed += 1;

	snakeBody.push_back(SnakeSegment(lastTailPosition));
}

void Snake::Reset() {
	snakeBody.clear();

	snakeBody.push_back(SnakeSegment(10, 10));
	snakeBody.push_back(SnakeSegment(10, 9));
	snakeBody.push_back(SnakeSegment(10, 8));

	lastTailPosition = sf::Vector2i(10, 8);

	SetDirection(Direction::None); // start off still.
	speed = 10;
	lives = 3;
	score = 0;
	lost = false;
}

void Snake::UpdateLastTailPosition() {
	lastTailPosition = snakeBody[snakeBody.size() - 1].position;
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
	UpdateLastTailPosition();
	Move();
	CheckCollision();
}

void Snake::Cut(int segments) {
	loseSound.play();
	textbox.Add("You ran into yourself and lost " +
		std::to_string(segments) + " segments");
	for (int i = 0; i != segments; ++i) {
		snakeBody.pop_back();
	}
	UpdateLastTailPosition();
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
	bodyRect.setFillColor(sf::Color::Cyan);

	for (auto itr = snakeBody.begin() + 1;
		itr != snakeBody.end(); ++itr)
	{
		bodyRect.setPosition(itr->position.x * size,
			itr->position.y * size);
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
