//
// Created by Сергей Апарин on 12.10.2018.
//

#ifndef TP_CPP_PROJECT_GAME_H
#define TP_CPP_PROJECT_GAME_H

#include "MapObject.h"
#include <tmx/MapLoader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <tmx>


class Game
{
public:
    explicit Game(sf::RenderWindow &window);
    void start();

private:
    void gameLoop();
    void drawFrame();
    sf::RenderWindow &screen;
    GameObject ball;
    tmx::MapLoader ml;
};


#endif //TP_CPP_PROJECT_GAME_H
