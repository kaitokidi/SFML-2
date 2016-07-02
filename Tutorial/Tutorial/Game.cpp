#include "Game.h"

Game::Game() : window("Snake", sf::Vector2u(800, 600)),
	snake(world.GetBlockSize()), 
	world(sf::Vector2u(800, 600))
{
	clock.restart();
	srand(time(nullptr));

	elapsed = 0.0f;
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return clock.getElapsedTime(); }
void Game::RestartClock(){ elapsed += clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &window; }

void Game::HandleInput(){
	// Input handling.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		&& snake.GetDirection() != Direction::Down){
		snake.SetDirection(Direction::Up);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		&& snake.GetDirection() != Direction::Up){
		snake.SetDirection(Direction::Down);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		&& snake.GetDirection() != Direction::Right){
		snake.SetDirection(Direction::Left);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		&& snake.GetDirection() != Direction::Left){
		snake.SetDirection(Direction::Right);
	}
}

void Game::Update(){
	window.Update();
	float timestep = 1.0f / snake.GetSpeed();
	if(elapsed >= timestep){
		snake.Tick();
		world.Update(snake);
		elapsed -= timestep;
		if (snake.HasLost()){
			snake.Reset();
		}
	}
}

void Game::Render(){
	window.BeginDraw();
	// Render here.
	world.Render(window);
	snake.Render(window);

	window.EndDraw();
}