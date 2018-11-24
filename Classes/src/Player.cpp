//
//  Player.cpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Player.hpp"
#include "Globals.h"
#include "MyBuilding.hpp"

Player::Player(std::string nick, Vec2 pos)
{
    login = nick;
    spawnPoint = pos;
    auto object = new MyUnit(spawnPoint - Vec2(100, 400), 0);
    auto object2 = new MyUnit(spawnPoint -  Vec2(0, 400), 1);
    auto base = new MyBuilding(spawnPoint, "house.png");
    addUnit(base);
    addUnit(object);
    addUnit(object2);

    
}

void Player::addUnit(GameObject *unit)
{
    addChild(unit);
    sendNewUnitTCP();
    Globals::get_instance()->objects.push_back(unit);
    units[unit->id] = unit;
}

const std::map<unsigned int, GameObject *> Player::getUnits()
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
