#include "TextureManager.h"

TextureManager::TextureManager()
{
	manager["Default"];
}

TextureManager::~TextureManager()
{
}

void TextureManager::addTexture(std::string name, std::string fileName)
{
	if (manager.find(name) != manager.end()) // If it did not find anything then it is all good, texture doesn;t exist here yet.
		std::cerr << "Texture already exist in manager\n";

	manager[name].loadFromFile(fileName);
}

sf::Texture& TextureManager::getTexture(std::string s)
{
	if (manager.find(s) != manager.end())
		return manager[s];
}

