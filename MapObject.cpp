//
// Created by Сергей Апарин on 13.10.2018.
//
#include "MapObject.h"

GameObject::GameObject(sf::RenderWindow &window, unsigned int size):
            window(window),
            coordinates(1, 1),
            colorBody(sf::Color::Green),
            size(size)
{
    body.setRadius(size);
    body.setPosition(coordinates);
    body.setFillColor(colorBody);
}

void GameObject::drawObject()
{
    window.draw(body);
}

void GameObject::move(sf::Vector2f d)
{
    coordinates += d;
    body.setPosition(coordinates);
}