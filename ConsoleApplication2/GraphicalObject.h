#ifndef GRAPHICAL_OBJECT_CLASS
#define GRAPHICAL_OBJECT_CLASS

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "PhysicalObject.h"

// When creating it needs:
// 1. set the textre for rectangle (after setting it's size etc.)  (not texture rect, that is already in the update() loop)
// 1.1 Set the InTRect texture?
// 2. Set the animation parameters

class GraphicalObject : public PhysicalObject
{
public:
	sf::RectangleShape rectangle;
	Animation animation;

	//constructors and destructors
	GraphicalObject();
	~GraphicalObject();
	
	void update(float deltaTime);

	void render(sf::RenderWindow* win, float deltaTime);

	// It's not used by the class but by user to set for ex. iniatial position of the object
	void setPositionExternal(sf::Vector2f newPos);

	void setSizeMidOriginRect(sf::Vector2f newSize);

	void prepAnimParams(sf::Texture* t, sf::Vector2u imageCount, float switchTime);

};

#endif // !GRAPHICAL_OBJECT_CLASS

