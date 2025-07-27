#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	
	Animation();
	
	~Animation();

	void setParamters(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); // Used only when you use the default constructor. 

	void update(int row, float deltaTime);

	sf::IntRect uvRect;
};

