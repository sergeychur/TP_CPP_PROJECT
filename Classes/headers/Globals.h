//
//  Globals.h
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#ifndef Globals_h
#define Globals_h
#include "GameObject.hpp"
#include "Player.hpp"

class Globals
{
public:
    Globals();
    static Globals * instance;
    std::vector<GameObject*> objects;
    TMXTiledMap* map;
    unsigned int globalId;
    size_t requiredPlayersCount;
    Point positionToTileCoordinate(Point point);
    static Globals * get_instance()
    {
        if (!instance)
            instance = new Globals();
        return instance;
            
    }
};


#endif /* Globals_h */
