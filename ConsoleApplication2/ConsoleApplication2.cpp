
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
	return 0;
}