#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class MainMenu
{
public:
	//Constructor
	MainMenu(const sf::Font& font, const sf::Font& font_title);

	// 1. render : MainMenu rendering
	// 2. handleMouseInput : event react based on Mouse position
	// 3. getSelectedOption : return the selected option
	void render(sf::RenderWindow& window) const;
	void handleMouseInput(const sf::Vector2f& mousePos);
	int getSelectedOption() const;

private:
	sf::Text titleText;
	sf::Text playButton;
	sf::Text infoButton;
	sf::Text exitButton;
	sf::Text madeby;

	sf::RectangleShape background_r;
	sf::Texture background;
	sf::Sprite background_sprite;

	// Menu option
	enum MenuOption
	{
		Play = 0,
		Info,
		Exit,
		None
	};

	int selectedOption;

	// 1. initializeText : reset the text
	// 2. positionText : set the text position
	// 3. setupBackground : set background
	void initializeTexts(const sf::Font& font, const sf::Font& font_title);
	void positionTexts();
	void setupBackground();
};

#endif
