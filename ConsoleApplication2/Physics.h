#ifndef PHYSICS_CLASS
#define PHYSICS_CLASS
#include <SFML/Graphics.hpp>

#include "PhysicalObject.h"

class Physics {
public:
	Physics();

	~Physics();

	// Returns distance between two points
	static float distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);

	static float vectorLength(sf::Vector2f v);

	static sf::Vector2f makeVersor(sf::Vector2f v);

	static float dotProduct(sf::Vector2f v, sf::Vector2f u);

	// Adds the gravity force for the second object. We assume gravity acts from p1 to p2. (p2 will be attracted by p1 as if p1 had a fixed position)
	// And so force will be set onry for p2
	static void applyGravityForce(PhysicalObject& p1, PhysicalObject& p2);

	// Add anothoer force, thurst. Angle specifies direction from the x- axis in which we will be accelerating
	static void applyThrust(PhysicalObject& p, float thrustValue, float angle);

};

#endif