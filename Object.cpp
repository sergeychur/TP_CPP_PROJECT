//
// Created by Сергей Апарин on 13.10.2018.
//
#include "Object.h"

Object::Object(sf::RenderWindow &window, unsigned int size):
            window(window),
            coordinates(1, 1),
            colorBody(sf::Color::Green),
            size(size)
{
    body.setRadius(size);
    body.setPosition(coordinates);
    body.setFillColor(colorBody);
}

void Object::drawObject()
{
    window.draw(body);
}