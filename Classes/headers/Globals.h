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
#include "EnemyPlayer.hpp"
#include "ClientNetObject.h"
#include <memory>
#include "../../shared_files/include/command.hpp"
#include "../../shared_files/include/update.hpp"


const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;


#define WarriorPlist "warriorAnim.plist"
#define WarriorFormat "s_w_torso_move_%04d.tga"
#define DefaultSprite "s_w_torso_move_0004.tga"


class Globals
{
public:
    Globals();
    static Globals * instance;
    TMXTiledMap* map;
    Point positionToTileCoordinate(Point point);
    Point mapOffset;
    unsigned int mapMoveSpeed;
    std::unique_ptr<Player> player;
    ClientNetObject *net;
    std::map<unsigned int, std::unique_ptr<EnemyPlayer>> enemies;
    bool sendCheck;
    bool sendPop;
    static Globals * get_instance()
    {
        if (!instance)
            instance = new Globals();
        return instance;
            
    }
};


#endif /* Globals_h */
