//
//  EnemyUnit.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#include "EnemyUnit.hpp"


EnemyUnit::EnemyUnit(Vec2 pos, unsigned int id, std::string plist, std::string format) : GameObject(pos, plist, format, 23)
{
    GameObject::id = id;
    scheduleUpdate();
}

void EnemyUnit::onMouseDown(Event *event)
{
   
}

void EnemyUnit::update(float time)
{
    if (state == Move)
    {
        if(runAnim->isDone())
        {
            runAnim->startWithTarget(sprite);
        }
        runAnim->step(time);
    }
    else if (state == Fight)
    {
        if (fightAnim->isDone())
        {
            fightAnim->startWithTarget(sprite);
        }
        fightAnim->step(time);
    }
    else
    {
        sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("s_w_torso_move_0004.tga")->getSpriteFrame());
    }
    sprite->setPosition(position);
}

bool EnemyUnit::recieveUnitUnfoUDP()
{
    return true;
}
