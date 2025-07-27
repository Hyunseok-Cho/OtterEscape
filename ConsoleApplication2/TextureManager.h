#ifndef TEXTUREMANAGER_CLASS
#define TEXTUREMANAGER_CLASS

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

struct TextureManager {

	std::map<std::string, sf::Texture> manager;

	TextureManager();

	~TextureManager();

	void addTexture(std::string name, std::string fileName);

	sf::Texture& getTexture(std::string s);

};

#endif // !TEXTUREMANAGER_CLASS
