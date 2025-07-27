#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);//width so x also has to be a float 
	uvRect.height = texture->getSize().y / float(imageCount.y);//height so y also has to be a float 

}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::setParamters(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);//width so x also has to be a float 
	uvRect.height = texture->getSize().y / float(imageCount.y);//height so y also has to be a float 
}

void Animation::update(int row, float deltaTime)
{
	currentImage.y = row; //y so rows
	totalTime += deltaTime;//incrementing the time
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++; //switch to the next frame
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.left = currentImage.x * uvRect.width; //left coord of the rectangle
	uvRect.top = currentImage.y * uvRect.height; //same with top
}
