#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(sf::Vector2f p, sf::Vector2f v)
{
	this->pos = p;
	this->velocity = v;

	this->rectangle.setSize(sf::Vector2f(100.0f, 100.0f));
	this->rectangle.setOrigin(50.0f, 50.0f);

}

PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::applyForces(float deltaTime)
{
	sf::Vector2f vel = this->velocity;
	sf::Vector2f force;

	for (auto& f : forces) {
		force.x += f.x;
		force.y += f.y;
	}

	std::cout << "Force: " << force.x << " " << force.y << "\n";

	vel.x += force.x * deltaTime;
	vel.y += force.y * deltaTime;

	this->velocity = vel;

	this->forces.clear();

}

void PhysicalObject::updatePosition(float deltaTime)
{
	sf::Vector2f p = this->pos;
	sf::Vector2f v = this->velocity;

	p.x += v.x * deltaTime / 2.0f; // /2.0f becayse integration works like that?
	p.y += v.y * deltaTime / 2.0f;

	this->pos = p;

	std::cout << "Velocity: " << v.x << " " << v.y << "\n";
	std::cout << "pos: " << p.x << " " << p.y << "\n";

	// Temp feature
	rectangle.setPosition(p);
}

void PhysicalObject::updatePhysics(float deltaTime)
{
	this->applyForces(deltaTime);
	this->updatePosition(deltaTime);
}
