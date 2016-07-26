#include "Game.h"

static const size_t	WIDTH	= 20 * 40;
static const size_t HEIGHT	= 20 * 30;

Game::Game() :
	window("Snake", sf::Vector2u(WIDTH, HEIGHT)),
	world(sf::Vector2u(WIDTH, HEIGHT)),
	snake(world.GetBlockSize(), textbox),
	textbox(5, 14, 350, sf::Vector2f(225, 0))
{
	clock.restart();
	srand(time(nullptr));
	textbox.Add("Seeded random number generator with: " +
		std::to_string(time(nullptr)));

	elapsed = 0.0f;
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return clock.getElapsedTime(); }
void Game::RestartClock(){ elapsed += clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &window; }

void Game::HandleInput(){
	// Input handling.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		&& snake.GetPhyiscalDirection() != Direction::Down){
		snake.SetDirection(Direction::Up);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		&& snake.GetPhyiscalDirection() != Direction::Up){
		snake.SetDirection(Direction::Down);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		&& snake.GetPhyiscalDirection() != Direction::Right){
		snake.SetDirection(Direction::Left);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		&& snake.GetPhyiscalDirection() != Direction::Left){
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
	textbox.Render(window);

	window.EndDraw();
}