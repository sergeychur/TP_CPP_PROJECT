//
//  MyUnit.hpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#ifndef MyUnit_hpp
#define MyUnit_hpp
#include "GameObject.hpp"


class MyUnit : public GameObject
{
public:
    MyUnit(Vec2 pos, unsigned int id = 0);
private:
    unsigned int id;
    void update(float time);
    void onMouseDown(Event *event) ;
    void updateSprite(float time);
    void updatePosition(float time);
    bool sendUnitInfoUDP();
};

#endif /* MyUnit_hpp */
