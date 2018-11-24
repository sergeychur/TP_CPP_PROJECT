//
//  Globals.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#include "Globals.h"

Globals* Globals::instance = 0;

Globals::Globals():
        requiredPlayersCount(1),
        mapMoveSpeed(150)
{
    mapOffset = Point(0, 0);
}

Point Globals::positionToTileCoordinate(Point position)
{
    int x = static_cast<int>(position.x / map->getTileSize().width);
    int y = static_cast<int>(map->getMapSize().height -  position.y / map->getTileSize().height);
    return Point(x, y);
}
