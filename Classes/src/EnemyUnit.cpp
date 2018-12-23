//
//  EnemyUnit.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//

#include "EnemyUnit.hpp"
#include "Globals.h"

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
    if (isAlive) {
        if (state == Move) {
            if (runAnim->isDone()) {
                runAnim->startWithTarget(sprite);
            }
            runAnim->step(time);
        } else if (state == Fight) {
            if (fightAnim->isDone()) {
                fightAnim->startWithTarget(sprite);
            }
            fightAnim->step(time);
        } else {
            sprite->setSpriteFrame(Sprite::createWithSpriteFrameName(DefaultSprite)->getSpriteFrame());
        }
        sprite->setPosition(position);
        auto percent = (static_cast<double>(hp) / static_cast<double>(max_hp)) * 100;
        loadingBar->setPercent(percent);
    }
}

bool EnemyUnit::recieveUnitUnfoUDP()
{
    return true;
}
