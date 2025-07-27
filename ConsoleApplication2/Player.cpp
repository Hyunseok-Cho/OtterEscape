#include "Player.h"
#include "Physics.h"
#include "PhysicalObject.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>



Player::Player(float x, float y): rotation(-90.f), fuel(100.0f), position(x, y)
{
	// Initialize position
    velocity = sf::Vector2f(0.0f, 0.0f);

    // Initialize graphical representation
    rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
    rectangle.setOrigin(25.0f, 25.0f); // Center origin for rotation
    rectangle.setPosition(position);
    //rectangle.setFillColor(sf::Color::Green);

    rectangle.setRotation(-90.0f);

}

void Player::handleInput(const sf::Keyboard& keyboard, float deltaTime)
{
	if (keyboard.isKeyPressed(sf::Keyboard::W))
	{
		accelerate();
        consumeFuel(deltaTime);
	}
    if (keyboard.isKeyPressed(sf::Keyboard::A))
    {
        rotateLeft();
    }
    if (keyboard.isKeyPressed(sf::Keyboard::D))
    {
        rotateRight();
    }
}

void Player::accelerate()
{
    // Apply thrust in the direction of the player's rotation
    float angleInRadians = rotation * (M_PI / 180.0f);
    Physics::applyThrust(*this, ACCELERATION_FORCE, angleInRadians);
}

void Player::rotateLeft()
{
    rotation -= ROTATION_SPEED * 0.016f; // Assume 60 FPS (~16ms per frame)
    if (rotation < 0)
    {
        rotation += 360.0f;
    }
    rectangle.setRotation(rotation);
}

void Player::rotateRight()
{
    rotation += ROTATION_SPEED * 0.016f; // Assume 60 FPS (~16ms per frame)
    if (rotation >= 360.0f)
    {
        rotation -= 360.0f;
    }
    rectangle.setRotation(rotation);
}

void Player::update(float deltaTime)
{
    // Update physics (position and velocity)
    updatePhysics(deltaTime);
    //updatePosition(deltaTime);
    position += velocity * deltaTime;
    
    //Update Graphical representation
    rectangle.setPosition(position); // pos
    rectangle.setRotation(rotation);

    this->animation.update(0, deltaTime);
    this->rectangle.setTextureRect(animation.uvRect);

    // Update Consuming Fuel
    //consumeFuel(deltaTime);
}

void Player::render(sf::RenderWindow& window)
{
    // Render the player to the window.
    window.draw(rectangle);
}

void Player::consumeFuel(float deltaTime)
{
    if (velocity.x != 0.0f || velocity.y != 0.0f) // Consume Fuel when moving
    {
        fuel -= 10.0f * deltaTime; // Ratio of consuming fuel
    }
}

sf::Vector2f Player::getPosition() const
{
    return position;
}

sf::Vector2f Player::getVelocity() const
{
    return velocity;
}

float Player::getFuel() const
{
    return fuel;
}

bool Player::isOutOfFuel() const
{
    return fuel <= 0.0f;
}