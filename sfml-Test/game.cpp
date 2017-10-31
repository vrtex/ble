#include "game.h"

Game::Game(sf::RenderWindow *w) :
    window(w)
{
    w->create(sf::VideoMode(512, 512), "Title");
    w->setFramerateLimit(60);
}

void Game::runMainLoop()
{
    sf::Event e;
    while(window->isOpen())
    {
        window->clear();
        while(window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window->close();
        }
        wonsz.draw(window);
        window->display();
    }
}

Game::~Game()
{
}
