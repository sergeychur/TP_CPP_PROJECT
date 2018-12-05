//
//  Level.hpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#ifndef Level_hpp
#define Level_hpp
#include "cocos2d.h"

using namespace cocos2d;

class Level : public cocos2d::Node
{
public:
    TMXTiledMap *map;
    void loadMap(std::string name);
    TMXTiledMap * getMap();
    ~Level();
};

#endif /* Level_hpp */
