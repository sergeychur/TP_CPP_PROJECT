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
    Player(size_t id, Vec2 pos);
    void addUnit(int x, int y, int h);
    std::map<unsigned int, std::unique_ptr<GameObject>>& getUnits();
    size_t id;
protected:
    bool isAlive;
    Vec2 spawnPoint;
    std::map<unsigned int, std::unique_ptr<GameObject>> units;
    void update(float time);
    void onMouseDown(Event *event) ;
    int unitsOffset;
    bool addedUnit = false;
    float timeSinceAdd = 0;
};

#endif /* Player_hpp */
