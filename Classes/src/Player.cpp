//
//  Player.cpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Player.hpp"
#include "Globals.h"
#include "MyBuilding.hpp"
#include "command.hpp"

Player::Player(size_t id, Vec2 pos) : spawnPoint(pos), id(id)
{
    auto mainLayer = Globals::get_instance()->map->getLayer("Background");
    auto mapPos = Globals::get_instance()->positionToTileCoordinate(spawnPoint);
    mainLayer->getTileAt(mapPos)->setColor(Color3B::RED);
    addUnit(spawnPoint.x - 100, spawnPoint.y);
}

void Player::addUnit(int x, int y)
{
    std::vector<int> a = {x , y , 75 , 100 , 1, 75, 1};
    Command com(this->id, 0,"create_unit", a);
    Globals::get_instance()->net->send(&com);
}

std::map<unsigned int, std::unique_ptr<GameObject>>& Player::getUnits()
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
