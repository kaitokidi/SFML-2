#include "World.h"
#include "Window.h"

World::World(sf::Vector2u windSize){
	blockSize = 16;

	windowSize = windSize;
	RespawnApple();
	appleShape.setFillColor(sf::Color::Magenta);
	appleShape.setRadius(blockSize / 2);

	for(int i = 0; i < 4; ++i){
		bounds[i].setFillColor(sf::Color(150,0,0));
		if(!((i + 1) % 2)){
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		} else {
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
		}
		if(i < 2){
			bounds[i].setPosition(0,0);
		} else {
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(sf::Vector2f(windowSize));
		}
	}
}

World::~World(){}

int World::GetBlockSize(){ return blockSize; }

void World::RespawnApple(){
	int maxX = (windowSize.x / blockSize) - 2;
	int maxY = (windowSize.y / blockSize) - 2;
	item = sf::Vector2i(
		rand() % maxX + 1, rand() % maxY + 1);
	appleShape.setPosition(
		item.x * blockSize,
		item.y * blockSize);
}

void World::Update(Snake& player){
	if(player.GetPosition() == item){
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}

	int gridSize_x = windowSize.x / blockSize;
	int gridSize_y = windowSize.y / blockSize;

	if(player.GetPosition().x <= 0 ||
		player.GetPosition().y <= 0 ||
		player.GetPosition().x >= gridSize_x - 1 ||
		player.GetPosition().y >= gridSize_y - 1)
	{
			player.Lose();
	}
}

void World::Render(Window& window){
	for(int i = 0; i < 4; ++i){
		window.Draw(bounds[i]);
	}
	window.Draw(appleShape);
}