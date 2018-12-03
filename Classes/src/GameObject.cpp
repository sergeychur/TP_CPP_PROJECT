//
//  GameObject.cpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//
#include <iostream>
#include "GameObject.hpp"

GameObject::GameObject(Vec2 pos, std::string plist, std::string format, int count) :
    position(pos),
    speed(75),
    isSelect(false),
    state(None),
    AttackedBy(nullptr),
    attackedObj(nullptr),
    minDistance(2),
    initRotation(-90),
    newPos(pos),
    hp(100),
    dmg(4)
{
    animationInit(runAnim, plist, format, count, true);
    animationInit(fightAnim, "f.plist", "s_w_sw_attack_02_%04d.tga", 22, false);
    sprite->setPosition(position);
    sprite->setAnchorPoint(Vec2(0.5, 0.75));
    addChild(sprite);
}

void GameObject::animationInit(Animate*& Anim, std::string plist, std::string format, int count, bool setSprite)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    frames = getAnimation(format, count);
    if (setSprite)
        sprite = Sprite::createWithSpriteFrame(frames.front());
    Anim = Animate::create(Animation::createWithSpriteFrames(frames, 1.0f/30));
    Anim->getAnimation()->setRestoreOriginalFrame(true);
    Anim->setDuration(0.80f);
    Anim->setTarget(sprite);
    Anim->retain();
}

Vector<SpriteFrame*> GameObject::getAnimation(std::string format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 0; i <= count; i++)
    {
        sprintf(str, format.c_str(), i * 2);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

const Vec2& GameObject::getPos()
{
    return position;
}

void GameObject::setPos(Point newPos)
{
    position = newPos;
}