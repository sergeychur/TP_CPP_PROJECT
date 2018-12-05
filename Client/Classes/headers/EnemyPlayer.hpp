//
//  EnemyPlayer.hpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#ifndef EnemyPlayer_hpp
#define EnemyPlayer_hpp

#include "GameObject.hpp"
USING_NS_CC;

class EnemyPlayer : public Node
{
public:
    EnemyPlayer(unsigned int id, Vec2 spawnPoint);
    std::map<unsigned int, std::unique_ptr<GameObject>> units;
    void addUnit(GameObject *unit);
    size_t id;
    Point spawnPoint;

};



#endif /* EnemyPlayer_hpp */
