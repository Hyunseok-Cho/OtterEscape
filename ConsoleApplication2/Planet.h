#ifndef PLANET_CLASS
#define PLANET_CLASS

#include "GraphicalObject.h"
#include "Physics.h"

// We have to set 

class Planet : public GraphicalObject{
public:
	sf::Vector2f orbitCenter; // Position relative to the left corcer of the screen -> 

	float orbitTravellingTime; // How much time it takes to jump between two discrete points of the orbit

	float velocityMag;

	std::vector<sf::Vector2f> path;
	int destinationIndex;

	Planet();

	~Planet();

	// Chose points for the path
	// Calculate speed with which it is supposed to move
	// It also sets the initial position for both physicalObject and rectangle
	void createPath(sf::Vector2f origin, float radius, float intAngle);

	// Not the same as update -> it only updates the current destination point and changes the velocity vector
	void followPath(float deltaTime);

	// Follows the path this->followPath and calls ->update() of the GraphicalObject
	void updatePlanet(float deltaTime);

};

#endif // !PLANET_CLASS
