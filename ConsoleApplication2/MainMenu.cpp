#include "MainMenu.h"
#include "Game.h"

float targetWidth = 1300;
float targetHeight = 700;


MainMenu::MainMenu(const sf::Font& font, const sf::Font& font_title) : selectedOption(None)
{
	setupBackground();
	initializeTexts(font, font_title);
	positionTexts();
}

void MainMenu::setupBackground()
{

	background.loadFromFile("Graphics/Background_MainMenu.png");
	background_sprite.setTexture(background);
	background_sprite.setScale(
		targetWidth / background.getSize().x, 
		targetHeight / background.getSize().y);
	background_sprite.setPosition(0, 0);
}

void MainMenu::initializeTexts(const sf::Font& font, const sf::Font& font_title)
{
	// Title
	titleText.setFont(font_title);
	titleText.setString("Hyperion");  // Title of Game
	titleText.setCharacterSize(80);
	titleText.setFillColor(sf::Color::White);

	// Play Button
	playButton.setFont(font);
	playButton.setString("Play");
	playButton.setCharacterSize(50);
	playButton.setFillColor(sf::Color::White);

	//Info Button
	infoButton.setFont(font);
	infoButton.setString("Info");
	infoButton.setCharacterSize(50);
	infoButton.setFillColor(sf::Color::White);

	//Exit Button
	exitButton.setFont(font);
	exitButton.setString("Exit");
	exitButton.setCharacterSize(50);
	exitButton.setFillColor(sf::Color::White);

	//Made by
	madeby.setFont(font);
	madeby.setString("Made by Team Hyperion");
	madeby.setCharacterSize(35);
	madeby.setFillColor(sf::Color::Magenta);
}

void MainMenu::positionTexts()
{
	// Position of title
	titleText.setPosition(150.f, 200.f);

	// button positions
	float baseY = 300.f;
	float spacing = 50.f;

	madeby.setPosition(150.f, baseY);
	playButton.setPosition(150.f, baseY + spacing);
	infoButton.setPosition(150.f, baseY + 2 * spacing);
	exitButton.setPosition(150.f, baseY + 3 * spacing);
}

void MainMenu::render(sf::RenderWindow& window) const
{
	window.clear();
	window.draw(background_sprite);
	window.draw(titleText);
	window.draw(madeby);
	window.draw(playButton);
	window.draw(infoButton);
	window.draw(exitButton);
}

// Button color changing for emphasize based on Mouse position
void MainMenu::handleMouseInput(const sf::Vector2f& mousePos)
{
	if (playButton.getGlobalBounds().contains(mousePos))
	{
		selectedOption = Play;
		playButton.setFillColor(sf::Color::Yellow);
	}
	else
	{
		playButton.setFillColor(sf::Color::White);
	}

	if (infoButton.getGlobalBounds().contains(mousePos)) {
		selectedOption = Info;
		infoButton.setFillColor(sf::Color::Yellow);
	}
	else {
		infoButton.setFillColor(sf::Color::White);
	}

	if (exitButton.getGlobalBounds().contains(mousePos)) {
		selectedOption = Exit;
		exitButton.setFillColor(sf::Color::Yellow);
	}
	else {
		exitButton.setFillColor(sf::Color::White);
	}

}

int MainMenu::getSelectedOption() const {
	return selectedOption;
}