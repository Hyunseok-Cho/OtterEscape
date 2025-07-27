#ifndef PHYSICAL_OBJECT_CLASS
#define PHYSICAL_OBJECT_CLASS

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class PhysicalObject {
public:
	sf::RectangleShape rectangle;

	float gravityConst;

	sf::Vector2f pos;
	sf::Vector2f velocity; // Unit vector of length 1
	
	std::vector<sf::Vector2f> forces;

	PhysicalObject(sf::Vector2f p = sf::Vector2f(0,0), sf::Vector2f v = sf::Vector2f(0,0));

	~PhysicalObject();

	// ------------ Appying physics ------------ //

	void applyForces(float deltaTime);

	void updatePosition(float deltaTime);

	void updatePhysics(float deltaTime);


};

#endif
