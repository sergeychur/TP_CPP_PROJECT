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
{}

void EnemyPlayer::addUnit(GameObject *unit)
{
    units[unit->id] = unit;
    addChild(unit);
}
