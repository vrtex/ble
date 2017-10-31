#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "wunsz.h"

class Game
{
public:
    Game(sf::RenderWindow *w);
    void runMainLoop();
    ~Game();
private:
    sf::RenderWindow *window;
    Snake wonsz;
};

#endif /* end of include guard: GAME_H */
