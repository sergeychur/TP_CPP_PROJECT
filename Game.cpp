//
// Created by Сергей Апарин on 12.10.2018.
//

#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include <cstdlib>

Game::Game(sf::RenderWindow &w) :
        window(w) {
    map.LoadFromFile("/Users/sergejaparin/Documents/TP_CPP_PROJECT/XMLmap.tmx");
}

void Game::gameInit() {
    player = new Player("ser", sf::Vector2f(30, 30));
    Unit *unit = new Unit(window, player, "hero.png", 96, 96, sf::Vector2f(50, 80), 1);
    Unit *unit2 = new Unit(window, player, "hero.png", 96, 96, sf::Vector2f(50, 180), 1);
    player->addUnit(unit);
    player->addUnit(unit2);
}

void Game::drawFrame() {
    window.clear();
    map.Draw(window);
    for (auto p : player->getUnits()) {
        p->drawObject();
    }

}

void Game::gameLoop()
{
    gameInit();
    sf::Clock clock;
    while (true) {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        drawFrame();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                exit(0);
            for (auto p : player->getUnits()) {
                p->control(event);
            }
        }
        for (auto p : player->getUnits()) {
            p->update(elapsed.asMilliseconds());
        }
        window.display();
    }

}


void Game::start() {
    gameLoop();
}