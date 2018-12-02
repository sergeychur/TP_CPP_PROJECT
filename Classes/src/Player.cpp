//
//  Player.cpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Player.hpp"
#include "Globals.h"
#include "MyBuilding.hpp"

Player::Player(unsigned int id, Vec2 pos) : spawnPoint(pos)
{
    auto object = new MyUnit(spawnPoint - Vec2(100, 400), 0, WarriorPlist ,WarriorFormat);
    auto object2 = new MyUnit(spawnPoint -  Vec2(0, 400), 1, WarriorPlist, WarriorFormat);
    auto mainLayer = Globals::get_instance()->map->getLayer("Background");
    auto mapPos = Globals::get_instance()->positionToTileCoordinate(spawnPoint);
    mainLayer->getTileAt(mapPos)->setColor(Color3B::RED);
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
