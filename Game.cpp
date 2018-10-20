//
// Created by Сергей Апарин on 12.10.2018.
//

#include "Game.h"

Game::Game(sf::RenderWindow &window):
        ball(window, 50),
        screen(window)
{
    lvl.LoadFromFile("/Users/sergejaparin/Documents/TP_CPP_PROJECT/xmlmap.tmx");
}

void Game::drawFrame()
{
    screen.clear();
    lvl.Draw(screen);
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
                    ball.move(sf::Vector2f(0, -10));
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    ball.move(sf::Vector2f(0, 10));
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    ball.move(sf::Vector2f(10, 0));
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    ball.move(sf::Vector2f(-10, 0));
                }
            }
        }

        screen.display();
    }
}

void Game::start()
{
    gameLoop();
}