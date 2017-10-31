#include "game.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow w;
    Game g(&w);
    g.runMainLoop();
    return 0;
}
