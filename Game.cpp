//
// Created by Сергей Апарин on 12.10.2018.
//

#include "Game.h"
#include "Player.h"
#include "Unit.h"

Game::Game(sf::RenderWindow &w):
        window(w)
{
    map.LoadFromFile("/Users/sergejaparin/Documents/TP_CPP_PROJECT/xmlmap.tmx");
}

void Game::gameInit()
{
    player = new Player("ser", sf::Vector2f(30, 30));
    Unit* unit = new Unit(window, player, "qrosh.png", 50, 50, sf::Vector2f(30, 30), 1);
    player->addUnit(unit);
}

void Game::drawFrame()
{
    window.clear();
    map.Draw(window);
//    for (auto p : player->getUnits())
//    {
//        p->drawObject();
//    }

}

void Game::gameLoop()
{
    //gameInit();
    //sf::Clock clock;
    while (true)
    {
       // sf::Time elapsed = clock.restart();
        //sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
      //  sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(0);
//            for (auto p : player->getUnits())
//            {
//                p->control(event, pos);
//                p->update(elapsed.asMilliseconds());
//            }

        }
        drawFrame();
    }

        window.display();
    }


void Game::start()
{
    gameLoop();
}