#ifndef PLANET_MANAGER_CLASS

#include "TextureManager.h"
#include "Planet.h"

class PlanetManager {
public:
	TextureManager* textureManag;

	PlanetManager();

	~PlanetManager();

	std::vector<Planet> planets;

	void initPlanets(sf::RenderWindow* w);

	void updatePlanetManager(float deltaTime);

	void renderPlanets(sf::RenderWindow* w, float deltaTime);

};

#endif // !PLANET_MANAGER_CLASS
