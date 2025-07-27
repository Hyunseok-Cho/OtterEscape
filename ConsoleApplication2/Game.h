#ifndef GAME_HPP
#define GAME_HPP

#include<SFML/Graphics.hpp>
#include "UI.h"
#include "MainMenu.h"
#include "Player.h"
#include "TextureManager.h"
#include "PlanetManager.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
	void renderMainMenu();
	void renderCredit();

	enum GameState
	{
		MAIN_MENU,
		PLAYING,
		CREDITS,
		GAME_OVER,
		WIN
	};

	sf::RenderWindow* mWindow;
	sf::Font font;
	UI* ui;
	MainMenu* mainmenu;
	sf::Text creditsText;

	GameState currentState;

	Player player;

	// TextureManager

	TextureManager textureManager;

	// Planets manager

	PlanetManager planetsManager;

	sf::Clock clk;
	float deltaTime;

	// Credit text setting
	void setupCreditsText();
	sf::Texture background_credit;
	sf::Sprite background_credit_sprite;

	// 1. handleMainMenuEvents : Main Menu screen event
	// 2. handleCreditsEvents : Credit screen event
	void handleMainMenuEvents(sf::Event& event);
	void handleCreditsEvents(sf::Event& event);
	void handleGameOverEvents(sf::Event& event);
	void handleWinEvents(sf::Event& event);

	void renderGameOver();
	void renderWin();

	static const int WINDOW_WIDTH = 1300;
	static const int WINDOW_HEIGHT = 700;  

	sf::RectangleShape goal;
	bool isGoalReached();
	void updateGameWin();
};

#endif