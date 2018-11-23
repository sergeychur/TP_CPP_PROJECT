//
//  Level.cpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Level.hpp"
#include "Globals.h"

void Level::loadMap(std::string mapname){
    
    map = TMXTiledMap::create(mapname);
    addChild(map);
    Globals::get_instance()->map = map;
    map->retain();
}

TMXTiledMap * Level::getMap(){
    return map;
}

Level::~Level()
{
    map->release();
}
