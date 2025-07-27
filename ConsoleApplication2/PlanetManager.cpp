#include "PlanetManager.h"

PlanetManager::PlanetManager()
{
}

PlanetManager::~PlanetManager()
{
}

void PlanetManager::initPlanets(sf::RenderWindow* w)
{
	planets.resize(4);

	// Order of planets
	// Saturn - middle
	// Titan
	// Jean
	// Hyperion
	//

	// Set params for saturn and it's moons
	sf::Vector2f midPoint = sf::Vector2f(float(w->getSize().x) / 2.0f, float(w->getSize().y) / 2.0f);

	Planet& saturn = planets[0];

	// Set graphical properties
	saturn.setSizeMidOriginRect(sf::Vector2f(150.0f, 150.0f));
	saturn.setPositionExternal(midPoint);
	saturn.prepAnimParams(&textureManag->getTexture("Saturn"), sf::Vector2u(6, 1), 0.7f);
	//saturn.createPath(sf::Vector2f(float(w->getSize().x) / 2.0f, float(w->getSize().y) / 2.0f), 0.0f); // It's the 0'th elelemtn and so it will not be updated

	// Set physical proerties
	saturn.gravityConst = 1000000.0f;

	// ------------------------------------------------------------

	Planet& titan = planets[1];

	titan.setSizeMidOriginRect(sf::Vector2f(100.0f, 100.0f));
	titan.prepAnimParams(&textureManag->getTexture("Titan"), sf::Vector2u(3, 1), 0.7f);

	titan.createPath(midPoint, 300.0f, 0.0f);

	titan.gravityConst = 1000000.0f;
	//titan.setPositionExternal(); // It is already set by the create path
	// ------------------------------------------------------------

	Planet& Jean = planets[2];

	Jean.setSizeMidOriginRect(sf::Vector2f(70.0f, 70.0f));
	Jean.prepAnimParams(&textureManag->getTexture("Jean"), sf::Vector2u(3, 1), 0.7f);

	Jean.createPath(midPoint, 450.0f, 3.14/2.0f);

	Jean.gravityConst = 5000000.0f;
	// ------------------------------------------------------------

	Planet& Hyperion = planets[3];

	Hyperion.setSizeMidOriginRect(sf::Vector2f(100.0f, 100.0f));
	Hyperion.prepAnimParams(&textureManag->getTexture("Hyperion"), sf::Vector2u(3, 1), 0.7f);

	Hyperion.createPath(midPoint, 550.0f, 3.14 * 3.0f/2.0f);

	Hyperion.gravityConst = 8000000.0f;

}

void PlanetManager::updatePlanetManager(float deltaTime)
{
	for (int i = 1; i < planets.size(); i++) {

		planets[i].updatePlanet(deltaTime);
		planets[i].animation.update(0, deltaTime);
	}
	planets[0].updatePlanet(deltaTime);
	planets[0].animation.update(0, deltaTime); 
}


void PlanetManager::renderPlanets(sf::RenderWindow* w, float deltaTime)
{
	for (auto& pl : planets)
		w->draw(pl.rectangle);

}
