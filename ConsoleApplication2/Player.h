#pragma once
#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include <SFML/Graphics.hpp>
#include "GraphicalObject.h"

class Player : public GraphicalObject
{
public:
	Player(float x, float y);
	~Player() {};

	// Keyboard input
	void handleInput(const sf::Keyboard& keyboard, float deltaTime);

	// Updae from physics law
	void update(float deltaTime);

	//rendering
	void render(sf::RenderWindow& window);

	//Acceleration and rotating
	void accelerate();
	void rotateLeft();
	void rotateRight();

	// Getters for UI
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	float getFuel() const;

	// Game over condition : 0% Fuel
	bool isOutOfFuel() const;

private:
	// Const value of acc and rotate
	static constexpr float ACCELERATION_FORCE = 200.0f;
	static constexpr float ROTATION_SPEED = 360.0f;

	sf::Vector2f position;
	float rotation;
	float fuel;
	float speed;

	void consumeFuel(float deltaTime);
};

#endif
