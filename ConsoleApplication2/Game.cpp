#include "Game.h"
#include "UI.h"
#include"MainMenu.h"
#include <cmath>
#include "Player.h"
#include "MainMenu.h"

// -----------------------UI-------------------------

sf::Font font;
sf::Font font_title;
UI ui(font);
sf::RectangleShape goal;

/**
* Class of Whole structure
* Size of window, Frame rate
* set Font
*/
Game::Game() : currentState(MAIN_MENU), player(700.0f, 300.0f)
{
	mWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hyperion");
	mWindow->setFramerateLimit(60); // Frame rate 60 FPS

	if (!font.loadFromFile("Jersey15-Regular.ttf"))
	{
		throw std::runtime_error("Unable to load font!");
	}

	if (!font_title.loadFromFile("Audiowide-Regular.ttf"))
	{
		throw std::runtime_error("Unable to load title font!");
	}

	ui = new UI(font);
	mainmenu = new MainMenu(font, font_title);

	setupCreditsText();

	// Setup the grpahics manager

	this->textureManager.addTexture("Saturn", "Graphics/Saturn.png");
	this->textureManager.addTexture("Titan", "Graphics/Titan.png");
	this->textureManager.addTexture("Jean", "Graphics/Jane.png");
	this->textureManager.addTexture("Hyperion", "Graphics/Hyperion.png");
	this->textureManager.addTexture("OtterSpeeding", "Graphics/OtterSpeeding.png");
	this->textureManager.addTexture("OtterIdle", "Graphics/OtterIdle.png");

	player.prepAnimParams(&textureManager.getTexture("OtterSpeeding"), sf::Vector2u(4,1), 0.7f);
	

	// Setup planets

	planetsManager.textureManag = &textureManager;
	planetsManager.initPlanets(mWindow);

	//Setup player mass

	player.gravityConst = 1.0f;

	// Setup Goal
	goal.setSize(sf::Vector2f(50, 50));
	goal.setFillColor(sf::Color::Green);
	goal.setPosition(1000, 550);  
}

/**
* Function of showing "Info"
*/
void Game::setupCreditsText()
{
	// Credit Background
	background_credit.loadFromFile("Graphics/info.png");
	background_credit_sprite.setTexture(background_credit);
	background_credit_sprite.setScale(
		WINDOW_WIDTH / background_credit.getSize().x,
		WINDOW_HEIGHT / background_credit.getSize().y);
	background_credit_sprite.setPosition(100, 120);

	// Credit Text
	creditsText.setFont(font_title);
	creditsText.setCharacterSize(18);
	creditsText.setFillColor(sf::Color::White);
	creditsText.setPosition(100.f, 70.f);
	creditsText.setString(
		"Warrant Officer Luna Ripley \n\n\n"

		"How to play\n\n"
		"W - Accelerating\n"
		"A - Turning left\n"
		"D - Turning right\n\n\n"

		"Otter Escaping\n\n"
		"Developed by: [Milosz Liniewiecki, Magdalena Rapala, Hyunseok Cho / Hyperion]\n\n"
		"Game Concept:\n"
		"- Escaping from the Saturn and its orbits\n"
		"- Physics-based spacecraft movement\n\n"
		"Special Thanks:\n"
		"- SFML Library\n"
		"- Project Mentors\n\n"
		"Press ESC to return to Main Menu"
	);
}

Game::~Game()
{
	delete mWindow;
	delete ui;
	delete mainmenu;
}

/**
* Game running function
* Swich for "Main menu", "Play", "Info" 
*/
void Game::run()
{

	while (mWindow->isOpen())
	{
		processEvents();
		switch (currentState)
		{
		case MAIN_MENU:
			renderMainMenu();
			break;
		case PLAYING:
			update();
			render();
			break;
		case CREDITS:
			renderCredit();
			break;
		}
		
	}
}

/**
* Function of Operating "Playing"
* Keyboard and Mouse event
*/
void Game::processEvents()
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mWindow->close();
		}

		switch (currentState)
		{
		case MAIN_MENU:
			handleMainMenuEvents(event);
			break;
		case CREDITS:
			handleCreditsEvents(event);
			break;
		case PLAYING:
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				player.handleInput(sf::Keyboard(), deltaTime);
			}
		case GAME_OVER:
			if (player.getFuel() < 0.0f || player.getPosition().x >= 1300 || player.getPosition().x <= 0 || player.getPosition().y >= 700 || player.getPosition().y <= 0)
			{
				renderGameOver();
				handleGameOverEvents(event);
			}
			break;
		case WIN:
			if (player.getPosition() == goal.getPosition())
			{
				renderWin();
				handleWinEvents(event);
			}
		default:
			break;
		}
	}
}

void Game::update()
{
	//float deltaTime = 1.0f / 60.0f; // !!FIXED DELTA TIME!!
	deltaTime = clk.restart().asSeconds();
	player.prepAnimParams(&textureManager.getTexture("OtterSpeeding"), sf::Vector2u(4, 1), 0.7f);

	if (player.getFuel() < 0.0f)
	{
		currentState = GameState::GAME_OVER;
	}

	player.update(deltaTime); // Player Update
	ui->update(player.getPosition(), player.getVelocity(), player.getFuel());

	planetsManager.updatePlanetManager(deltaTime);

	for (auto& e : planetsManager.planets) {
		Physics::applyGravityForce(e, player);
	}
	
	if (player.getPosition() == goal.getPosition())
	{
		currentState = GameState::WIN;  
	}

}

void Game::render()
{
	mWindow->clear(sf::Color::Black); // will fix the background

	player.render(*mWindow);  // !!Player Rendering!!
	ui->render(*mWindow);

	planetsManager.renderPlanets(mWindow, deltaTime);

	mWindow->draw(goal);

	mWindow->display();
}

void Game::renderMainMenu()
{
	mWindow->clear(sf::Color::Black);  // will fix the background
	mainmenu->render(*mWindow);
	mWindow->display();
}
	
void Game::renderCredit() 
{
	mWindow->clear();
	mWindow->draw(background_credit_sprite);
	mWindow->draw(creditsText);
	mWindow->display();
}

/**
* Main Menu events
*/
void Game::handleMainMenuEvents(sf::Event& event) 
{
	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
		mainmenu->handleMouseInput(mousePos);
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			switch (mainmenu->getSelectedOption())
			{
			case 0: // PLAY
				currentState = PLAYING;
				break;
			case 1: // INFO
				currentState = CREDITS;
				break;
			case 2: // EXIT
				mWindow->close();
				break;
			}
		}
	}
}

/**
* Credit screen event
*/
void Game::handleCreditsEvents(sf::Event& event) 
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) // ESC
		{
			currentState = MAIN_MENU;
		}
	}
}

void Game::renderGameOver()
{
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("GAME OVER\nYour fuel has run out!\nPress ESC to go Main");
	gameOverText.setPosition(700.f, 300.f);
	mWindow->draw(gameOverText);
	mWindow->display();
}

void Game::handleGameOverEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) // ESC
		{
			player = Player(100.0f, 350.0f);

			player.prepAnimParams(&textureManager.getTexture("OtterIdle"), sf::Vector2u(4, 1), 0.7f);
			player.rectangle.setRotation(-90.0f);

			planetsManager.initPlanets(mWindow); 
			currentState = MAIN_MENU;
		}
	}
}

void Game::handleWinEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) // ESC
		{
			player = Player(100.0f, 350.0f);

			player.prepAnimParams(&textureManager.getTexture("OtterIdle"), sf::Vector2u(4, 1), 0.7f);
			player.rectangle.setRotation(-90.0f);

			planetsManager.initPlanets(mWindow);
			currentState = MAIN_MENU;
		}
	}
}

void Game::renderWin()
{
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(sf::Color::Magenta);
	gameOverText.setString("You Win\nYou reached the goal!\nPress ESC to go Main");
	gameOverText.setPosition(700.f, 300.f);
	mWindow->draw(gameOverText);
	mWindow->display();
}


