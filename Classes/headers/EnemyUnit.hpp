//
//  EnemyUnit.hpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#ifndef EnemyUnit_hpp
#define EnemyUnit_hpp
#include "GameObject.hpp"

class EnemyUnit : public GameObject
{
public:
    EnemyUnit(Vec2 pos);
private:
    void update(float time);
    void onMouseDown(Event *event);
    bool recieveUnitUnfoUDP();
};

#endif /* EnemyUnit_hpp */
