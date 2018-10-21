//
// Created by Сергей Апарин on 20.10.2018.
//

#include "Player.h"


Player::Player(std::string name, sf::Vector2f spPoint)
{
        nickName = name;
        spawnPoint = spPoint;
}

void Player::addUnit(GameObject * unit)
{
    units.push_back(unit);
}

const std::vector<GameObject*> Player::getUnits()
{
    return units;
}