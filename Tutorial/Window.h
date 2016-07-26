#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw(); // Clear the window.
	void EndDraw(); // Display the changes.

	void Update();

	bool IsDone() const;
	bool IsFullscreen() const;
	sf::Vector2u GetWindowSize() const;

	void ToggleFullscreen();

	void Draw(sf::Drawable& drawable);

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Destroy();
	void Create();

	sf::RenderWindow window;
	sf::Vector2u windowSize;
	std::string windowTitle;
	bool isDone;
	bool isFullscreen;
};

#endif