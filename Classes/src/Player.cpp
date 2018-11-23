//
//  Player.cpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Player.hpp"
#include "Globals.h"

Player::Player(std::string nick, Vec2 pos)
{
    login = nick;
    spawnPoint = pos;
    auto object = new MyUnit(spawnPoint);
    auto object2 = new MyUnit(spawnPoint -  Vec2(0, 200));
    addUnit(object);
    addUnit(object2);
    
}

void Player::addUnit(GameObject *unit)
{
    addChild(unit);
    sendNewUnitTCP();
    Globals::get_instance()->objects.push_back(unit);
    units.push_back(unit);
}

const std::vector<GameObject *> Player::getUnits()
{
    return units;
}

void Player::update(float delta)
{
    
}

bool Player::sendNewUnitTCP()
{
    return true;
}
