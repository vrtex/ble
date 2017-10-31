#ifndef WUNSZ_H
#define WUNSZ_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class Node
{
public:
    Node(sf::Vector2u pos);
    Node(sf::Texture *pic, sf::Vector2u pos);
    void setPicture(sf::Texture *pic);
    sf::Vector2u getPosition() const;
    void draw(sf::RenderWindow *w);
    ~Node();
protected:
    sf::Vector2u position;
    sf::Vector2u blobSize;
    sf::Sprite body;
};

class HeadNode : public Node
{
public:
    HeadNode(sf::Vector2u pos, std::vector<Node> *t);
    void move(int x, int y);
    ~HeadNode();
private:
    sf::Texture headPic, tailPic;
    std::vector<Node> *tail;

};

class Snake
{
public:
    Snake();
    void update();
    void draw(sf::RenderWindow *w);
    ~Snake();
private:
    sf::Clock moveTimer;
    sf::Vector2i currentDirection;
    std::vector<Node> tail;
    HeadNode head;
};

#endif /* end of include guard: WUNSZ_H */
