#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "eee");
    sf::Event e;
    sf::RectangleShape r({50, 50});
    r.setPosition(50, 50);
    r.setOrigin(25, 25);
    float x;
    float rotation;
    while (window.isOpen())
    {
        window.clear();
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
                else if(e.type == sf::Event::KeyPressed)
                {

                    r.rotate(10);
                    rotation = r.getRotation() * M_PI / 180;
                    x = (r.getPoint(1).x - r.getOrigin().x) * cos(rotation) - (r.getPoint(1).y - r.getOrigin().y) * sin(rotation);
                    x += r.getPosition().x;
                }
        }
        window.draw(r);
        window.display();
    }
    return 0;
}
