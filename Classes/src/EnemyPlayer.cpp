//
//  EnemyPlayer.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#include "EnemyPlayer.hpp"
#include "Globals.h"

EnemyPlayer::EnemyPlayer(unsigned int id, Vec2 spawnPoint):
                            id(id),
                            spawnPoint(spawnPoint)
{
    auto mainLayer = Globals::get_instance()->map->getLayer("Background");
    auto mapPos = Globals::get_instance()->positionToTileCoordinate(spawnPoint);
    mainLayer->getTileAt(mapPos)->setColor(Color3B::RED);
}

void EnemyPlayer::addUnit(GameObject *unit)
{
    units[unit->id] = unit;
    addChild(unit);
}
