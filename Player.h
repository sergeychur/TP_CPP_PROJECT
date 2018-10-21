//
// Created by Сергей Апарин on 20.10.2018.
//

#ifndef TP_CPP_PROJECT_PLAYER_H
#define TP_CPP_PROJECT_PLAYER_H

class GameObject;

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(std::string name, sf::Vector2f spPoint);

    void addUnit(GameObject* unit);

    const std::vector<GameObject *> getUnits();

    ~Player();

private:
    std::string nickName;
    bool isAlive{true};
    sf::Vector2f spawnPoint;
    std::vector<GameObject*> units;
};


#endif //TP_CPP_PROJECT_PLAYER_H
