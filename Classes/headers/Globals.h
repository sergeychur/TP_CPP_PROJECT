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

const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;

class Globals
{
public:
    Globals();
    static Globals * instance;
    std::vector<GameObject*> objects;
    TMXTiledMap* map;
    size_t requiredPlayersCount;
    Point positionToTileCoordinate(Point point);
    Point mapOffset;
    unsigned int mapMoveSpeed;
    Player* player;
    static Globals * get_instance()
    {
        if (!instance)
            instance = new Globals();
        return instance;
            
    }
};


#endif /* Globals_h */
