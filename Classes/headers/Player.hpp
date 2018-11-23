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

USING_NS_CC;

class Player : public cocos2d::Node
{
public:
    Player(std::string name, Vec2 pos);
    
    void addUnit(GameObject* unit);
    
    const std::vector<GameObject *> getUnits();
    
    
protected:
    std::string login;
    bool isAlive;
    Vec2 spawnPoint;
    std::vector<GameObject*> units;
    void update(float time);
    bool sendNewUnitTCP();
};

#endif /* Player_hpp */
