#include "Planet.h"

Planet::Planet()
{
	this->destinationIndex = 0;
}

Planet::~Planet()
{
}

void Planet::createPath(sf::Vector2f origin, float radius, float intAngle)
{
	sf::Vector2f point;

	// No you cannot push y = +sqrt, y = -sqrt at the same time, because then it will be going to bounce from bottom to top and reverse
	// Calculate the discrete points 
	for (int xx = origin.x - radius; xx < origin.x + radius; xx+=10.0f) {
		float y1, y2;
		point.x = xx;

		point.y = std::sqrt(std::pow(radius, 2) - std::pow(xx - origin.x, 2)) + origin.y;
		path.push_back(point);

		//point.y = -std::sqrt(std::pow(radius, 2) - std::pow(xx - origin.x, 2)) + origin.y;
		//path.push_back(point);
	}
	
	for (int xx = origin.x + radius; xx > origin.x - radius; xx -= 10.0f) {
		float y;
		point.x = xx;

		point.y = -std::sqrt(std::pow(radius, 2) - std::pow(xx - origin.x, 2)) + origin.y;
		path.push_back(point);
	}

	// Calculate the speed
	//?

	this->velocityMag = 400.0f;

	// Based on the init angle decide from which destinationIndex shall we start
	// Basiclly find such point whose distance from the theoritacal starting point (dictated by angle and radius) is the lowest
	int startIndex = 0;
	sf::Vector2f theoreticalStartingPos = sf::Vector2f(-radius * cos(intAngle), radius * sin(intAngle));

	float diff = 0.0f;
	float minDiff = 10000.0f;

	int i = 0;
	for (auto& p : path) {
		diff = Physics::distanceBetweenPoints(theoreticalStartingPos, path[i]);
		
		if (diff <= minDiff) {
			minDiff = diff;
			startIndex = i;
		}
	}

	destinationIndex = i + 1;

	if (destinationIndex >= path.size())
		destinationIndex = 0;

	this->setPositionExternal(path[startIndex]);
}

void Planet::followPath(float deltaTime)
{
	// 1. set the velocity vector
	// 2. Anticipate next step 
	// 3. If in the next we get farther away from the destination point, switch  the destination point ti next

	if (path.size() > 0) {

		sf::Vector2f versor;
		sf::Vector2f targetPos = path[destinationIndex];

		if (targetPos == this->pos) {
			destinationIndex++;

			return;
		}

		versor = targetPos - this->pos;
		versor = Physics::makeVersor(versor);

		sf::Vector2f vel;
		vel.x = versor.x * velocityMag;
		vel.y = versor.y * velocityMag;

		this->velocity = vel;

		// Check if the dot product is negative -> then change the destination point

		sf::Vector2f prevToDest = path[destinationIndex] - path[destinationIndex - 1]; // May generate problems

		float dotProd = Physics::dotProduct(versor, prevToDest);

		if (dotProd < 0)
			destinationIndex++;

		if (destinationIndex >= path.size()) {
			destinationIndex = 1;
		}

	}

	// Anticipate the result of the next step

	/*
	sf::Vector2f anticipatedPosition = this->pos;
	sf::Vector2f deltaPos = this->velocity;

	deltaPos.x *= deltaTime;
	deltaPos.y *= deltaTime;

	anticipatedPosition += deltaPos;
	
	float currentDistance = Physics::distanceBetweenPoints(this->pos, targetPos);
	float anticipatedDistance = Physics::distanceBetweenPoints(anticipatedPosition, targetPos);

	
	if (anticipatedDistance < currentDistance) {
		std::cout << "Changing target position to: " << path[destinationIndex].x << " " << path[destinationIndex].y << "\n";
		destinationIndex++;
	}
	
	// If in the next step we will start to get farther away it means we passed the destination piint and it's time to head to switch the destination
	if (destinationIndex >= path.size()) {
		destinationIndex = 0;
	}
	*/
}


void Planet::updatePlanet(float deltaTime)
{
	this->followPath(deltaTime);
	this->update(deltaTime);

}
