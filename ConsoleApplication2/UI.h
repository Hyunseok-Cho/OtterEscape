#pragma once
#ifndef UI_CLASS
#define UI_CLASS

#include <SFML/Graphics.hpp>

class UI
{
public:
	//Constructor with font
	UI(const sf::Font& font);
	~UI(){};

	// 1. update : updating the player's position, velocity, fuel information
	// 2. render : UI rendering (information box)
	void update(const sf::Vector2f& position, const sf::Vector2f& velocity, float fuel);
	void render(sf::RenderWindow& window) const;

private:
	sf::RectangleShape ui_background;
	sf::Text position;
	sf::Text velocity;
	sf::Text fuel;

	// updateText : update the text information
	void updateText();
	sf::Vector2f playerPosition;
	sf::Vector2f playerVelocity;
	float playerFuel;
};

#endif
