//
//  Player.hpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#ifndef Player_hpp
#define Player_hpp
#include "GameObject.hpp"
#include "MyUnit.hpp"
#include <vector>
#include <string>
#include <map>

USING_NS_CC;

class Player : public cocos2d::Node
{
public:
    Player(unsigned int id, Vec2 pos);
    
    void addUnit(GameObject* unit);
    
    const std::map<unsigned int, GameObject *> getUnits();
    
    
protected:
    unsigned int id;
    bool isAlive;
    Vec2 spawnPoint;
    std::map<unsigned int, GameObject*> units;
    void update(float time);
    bool sendNewUnitTCP();
};

#endif /* Player_hpp */
