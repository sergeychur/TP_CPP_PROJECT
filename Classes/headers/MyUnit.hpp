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
    explicit MyUnit(Vec2 pos, unsigned int id);
private:
    void update(float time) override;
    void onMouseDown(Event *event) ;
    void updateSprite(float time);
    void updatePosition(float time);
    void startMoving();
    void stopMoving();
    bool sendUnitInfoUDP();
};

#endif /* MyUnit_hpp */
