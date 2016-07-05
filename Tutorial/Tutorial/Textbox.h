#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <vector>

#include <SFML\Graphics.hpp>

#include "Window.h"

using MessageContainer = std::vector <std::string>;

class Textbox {
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox();

	void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void Add(const std::string& message);
	void Clear();

	void Render(Window& window);
private:
	MessageContainer messages;
	int numVisible;

	sf::RectangleShape backdrop;
	sf::Font font;
	sf::Text content;
};

#endif