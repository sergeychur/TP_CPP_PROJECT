//
//  GameObject.cpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//
#include <iostream>
#include "GameObject.hpp"
#include "Globals.h"
GameObject::GameObject(Vec2 pos, std::string plist, std::string format, int count) :
    position(pos),
    speed(75),
    isSelect(false),
    state(None),
    minDistance(2),
    initRotation(-90),
    newPos(pos),
    hp(1000),
    max_hp(1000),
    dmg(1),
    remoteFight(false)
{
    animationInit(runAnim, plist, format, count, true);
    animationInit(fightAnim, "f.plist", "s_w_sw_attack_02_%04d.tga", 22, false);
    sprite->setPosition(position);
    sprite->setAnchorPoint(Vec2(0.5, 0.75));
    loadingBar = ui::LoadingBar::create("lb.png");
    loadingBar->setScale(0.2);
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    loadingBar->setPercent((hp / max_hp) * 100);
    loadingBar->setPosition(Vec2(70, 0));
    loadingBar->setColor(Color3B::RED);
    sprite->addChild(loadingBar);
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

void GameObject::kill() {
    if (hp <= 0) {
        onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
        Globals::get_instance()->map->getLayer("Background")->getTileAt(onMap)->setColor(Color3B::WHITE);
        Globals::get_instance()->map->removeChild(this);
        isAlive = false;
    }
}