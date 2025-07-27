#include "GraphicalObject.h"

GraphicalObject::GraphicalObject() : PhysicalObject()
{
}

GraphicalObject::~GraphicalObject()
{
}

void GraphicalObject::update(float deltaTime)
{
	this->updatePhysics(deltaTime);

	this->animation.update(0, deltaTime);
	this->rectangle.setTextureRect(animation.uvRect);

	this->rectangle.setPosition(this->pos);

}

void GraphicalObject::render(sf::RenderWindow* win, float deltaTime)
{
	win->draw(rectangle);

}

void GraphicalObject::setPositionExternal(sf::Vector2f newPos)
{
	this->pos = newPos;
	this->rectangle.setPosition(newPos);
}

void GraphicalObject::setSizeMidOriginRect(sf::Vector2f newSize)
{
	this->rectangle.setSize(newSize);
	this->rectangle.setOrigin(newSize.x / 2.0f, newSize.y / 2.0f);

}

void GraphicalObject::prepAnimParams(sf::Texture* t, sf::Vector2u imageCount, float switchTime)
{
	this->rectangle.setTexture(t);
	this->animation.setParamters(t, imageCount, switchTime);

}
