//
// Created by Сергей Апарин on 13.10.2018.
//

#ifndef TP_CPP_PROJECT_OBJECT_H
#define TP_CPP_PROJECT_OBJECT_H


#include <SFML/Graphics.hpp>

class Object
{
public:
    explicit Object(sf::RenderWindow & w, unsigned int s);
    void drawObject();
    void move();


private:
    sf::RenderWindow &window;
    sf::Vector2f coordinates;
    sf::Color colorBody;
    sf::CircleShape body;
    unsigned int size;
};


#endif //TP_CPP_PROJECT_OBJECT_H
