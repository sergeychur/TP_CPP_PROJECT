//
// Created by Сергей Апарин on 13.10.2018.
//

#ifndef TP_CPP_PROJECT_OBJECT_H
#define TP_CPP_PROJECT_OBJECT_H


#include <SFML/Graphics.hpp>
#include "Player.h"

class GameObject {
public:
    explicit GameObject();

    explicit GameObject(sf::RenderWindow &w);

    virtual void drawObject();

    virtual void destroyObject();

    virtual float getXcoord();

    virtual float getYcoord();

    virtual ~GameObject();


protected:
    sf::RenderWindow &window;
    sf::Vector2f coordinates;
    sf::Sprite sprite;
    sf::Texture texture;
    Player &player;
    int price;
    int reward;
    float hitPoints;
    unsigned int id;

};


#endif //TP_CPP_PROJECT_OBJECT_H
