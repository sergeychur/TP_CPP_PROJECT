//
// Created by Сергей Апарин on 12.10.2018.
//

#ifndef TP_CPP_PROJECT_GAME_H
#define TP_CPP_PROJECT_GAME_H

#include "Object.h"

class Game
{
public:
    explicit Game(sf::RenderWindow &window);
    void start();

private:
    void gameLoop();
    void drawFrame();
    sf::RenderWindow &screen;
    Object ball;
};


#endif //TP_CPP_PROJECT_GAME_H
