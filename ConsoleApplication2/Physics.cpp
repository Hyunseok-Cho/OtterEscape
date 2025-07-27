#include "Physics.h"

Physics::Physics() {

}

Physics::~Physics() {

}

float Physics::distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

float Physics::vectorLength(sf::Vector2f v)
{
	return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
}

sf::Vector2f Physics::makeVersor(sf::Vector2f v)
{
	float mag = vectorLength(v);
	v.x = v.x / mag;
	v.y = v.y / mag;

	return v;
}

float Physics::dotProduct(sf::Vector2f v, sf::Vector2f u)
{
	return v.x * u.x + v.y * u.y;
}

void Physics::applyGravityForce(PhysicalObject& p1, PhysicalObject& p2)
{
	float r = distanceBetweenPoints(p1.pos, p2.pos);

	float F_mag = p1.gravityConst * p2.gravityConst / pow(r, 2);

	sf::Vector2f versor = p1.pos - p2.pos;

	std::cout << "versor: " << versor.x << " " << versor.y << "\n";

	versor = makeVersor(versor);

	//sf::Vector2f Force_1(versor.x * F_mag, versor.y * F_mag);
	sf::Vector2f Force_2(versor.x * F_mag, versor.y * F_mag);
	
	//p1.forces = Force_1;
	p2.forces.push_back(Force_2);
}

void Physics::applyThrust(PhysicalObject& p, float thrustValue, float angle)
{
	sf::Vector2f force;

	force.x = cos(angle);
	force.y = sin(angle);

	force.x *= thrustValue;
	force.y *= thrustValue;

	p.forces.push_back(force);
}
