#include "wunsz.h"

Node::Node(sf::Vector2u pos) :
    position(pos)
{
}

Node::Node(sf::Texture *pic, sf::Vector2u pos) :
    position(pos)
{
    std::cout << "hello\n";
    body.setTexture(*pic);
    blobSize = pic->getSize();
    body.setOrigin(blobSize.x / 2, blobSize.y / 2);
    body.setPosition(blobSize.x * position.x, blobSize.y * position.y);
}

void Node::setPicture(sf::Texture *pic)
{
    body.setTexture(*pic);
    blobSize = pic->getSize();
    body.setPosition(blobSize.x * position.x, blobSize.y * position.y);
    body.setOrigin(blobSize.x / 2, blobSize.y / 2);
}

sf::Vector2u Node::getPosition() const
{
    return position;
}

void Node::draw(sf::RenderWindow *w)
{
    w->draw(body);
}

Node::~Node()
{

}

//--------------------------------------------------------------------------------

HeadNode::HeadNode(sf::Vector2u pos, std::vector<Node> *t) : Node(pos)
{
    headPic.loadFromFile("Res/head.png");
    tailPic.loadFromFile("Res/tail.png");
    tail = t;
    tail->emplace_back(&tailPic, sf::Vector2u(pos.x - 1, pos.y));
    tail->emplace_back(&tailPic, sf::Vector2u(pos.x - 2, pos.y));
    setPicture(&headPic);
}


void HeadNode::move(int x, int y)
{
    tail->erase(tail->begin());
    tail->emplace_back(&tailPic, getPosition());
    position.x += x;
    position.y += y;
    body.setPosition(blobSize.x * position.x, blobSize.y * position.y);
}

HeadNode::~HeadNode()
{

}

//---------------------------------------------------------------------------------------

Snake::Snake() :
    head(sf::Vector2u(3, 2), &tail)
{
    currentDirection = {-1, 0};
    moveTimer.restart();
}

void Snake::update()
{
    if(moveTimer.getElapsedTime().asSeconds() > 1)
    {
        head.move(currentDirection.x, currentDirection.y);
        moveTimer.restart();
    }
}

void Snake::draw(sf::RenderWindow *w)
{
    head.draw(w);
    // head.move(1, 1);
    for(auto &t : tail)
    {
        t.draw(w);
    }
}

Snake::~Snake()
{

}
