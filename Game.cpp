//
// Created by Сергей Апарин on 12.10.2018.
//

#include "Game.h"

Game::Game(sf::RenderWindow &window):
        ball(window, 50),
        screen(window)
{

}

void Game::drawFrame()
{
    screen.clear();
    ball.drawObject();
}

void Game::gameLoop()
{
    bool loopRun = true;
    while (loopRun)
    {
        drawFrame();
        sf::Event event;
        while (screen.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                exit(0);
            }
        }
        screen.display();
    }
}

void Game::start()
{
    gameLoop();
}