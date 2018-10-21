//
// Created by Сергей Апарин on 13.10.2018.
//
#include "GameObject.h"

GameObject::GameObject(sf::RenderWindow &window, Player* player, std::string file, float w, float h, sf::Vector2f pos):
        window(window),
        player(player)

{
    health = 100;
    File = file;
    width = w;
    height = h;
    image.loadFromFile("/Users/sergejaparin/Documents/TP_CPP_PROJECT/Img/" + File);
    image.createMaskFromColor(sf::Color(0, 0, 255));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    coordinates = pos;
    //sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setOrigin(w / 2, h / 2);
}

float GameObject::getXcoord()
{
    return coordinates.x;
}

float GameObject::getYcoord()
{
    return coordinates.y;
}

void GameObject::drawObject()
{
    window.draw(sprite);
}

