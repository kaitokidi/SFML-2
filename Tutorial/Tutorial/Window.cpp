#include <SFML/Graphics.hpp>

#include "Window.h"

Window::Window() {
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	Setup(title, size);
}

Window::~Window() {
	Destroy();
}

void Window::BeginDraw() {
	window.clear(sf::Color::Black);
}

void Window::EndDraw() {
	window.display();
}

void Window::Update() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
		{
			ToggleFullscreen();
		}
	}
}

bool Window::IsDone() const {
	return isDone;
}

bool Window::IsFullscreen() const {
	return isFullscreen;
}

sf::Vector2u Window::GetWindowSize() const {
	return windowSize;
}

void Window::ToggleFullscreen() {
	isFullscreen = !isFullscreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& drawable) {
	window.draw(drawable);
}

void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	windowTitle = title;
	windowSize = size;
	window.setFramerateLimit(60); // 60 FPS cap.
	isFullscreen = false;
	isDone = false;
	Create();
}

void Window::Destroy() {
	window.close();
}

void Window::Create() {
	sf::Uint32 style = (isFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
}