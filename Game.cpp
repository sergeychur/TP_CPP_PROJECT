//
// Created by Сергей Апарин on 12.10.2018.
//

#include "Game.h"

Game::Game(sf::RenderWindow &window):
        ball(window, 50),
        screen(window),
        ml("/Users/sergejaparin/Documents/TP_CPP_PROJECT/XML")
{
    ml.load("dd.tmx");
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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    ball.move(sf::Vector2f(0, 2));
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    ball.move(sf::Vector2f(0, -2));
                }
            }
        }
        const auto& layers = ml.getLayers();

        screen.display();
    }
}

void Game::start()
{
    gameLoop();
}