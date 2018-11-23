//
//  MyUnit.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//


#include "MyUnit.hpp"
#include "Globals.h"

MyUnit::MyUnit(Vec2 pos, unsigned int id) : GameObject(pos, "warriorAnim.plist", "s_w_torso_move_%04d.tga", 23), id(id)
{
    auto eventListener = EventListenerMouse::create();
    eventListener->onMouseDown = CC_CALLBACK_1(MyUnit::onMouseDown, this);
    onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, sprite);
    mainLayer = Globals::get_instance()->map->getLayer("Background");
    obstacles = Globals::get_instance()->map->getLayer("Walls");
    if (obstacles)
        obstacles->setVisible(false);
    scheduleUpdate();
}


void MyUnit::onMouseDown(cocos2d::Event *event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    auto y = Director::getInstance()->getWinSize().height + mouseEvent->getLocationInView().y;
    if (isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        isSelect = false;
        sprite->setColor(Color3B::WHITE);
    }
    if (!isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        Point onmap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
        if(mainLayer->getTileAt(onmap)->getBoundingBox().containsPoint(Vec2(mouseEvent->getLocationInView().x, y)))
        {
            isSelect = true;
            sprite->setColor(Color3B::GREEN);
        }
    }
    if (isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        isSelect = false;
        isMove = true;
        sprite->setColor(Color3B::WHITE);
        target = Vec2(mouseEvent->getCursorX(), y);
        velocity = (target - position).getNormalized();
    }
}

void MyUnit::update(float time)
{
    if (!isMove)
        mainLayer->getTileAt(onMap)->setColor(Color3B::GREEN);
    else
        mainLayer->getTileAt(onMap)->setColor(Color3B::WHITE);
    updateSprite(time);
    updatePosition(time);
}

void MyUnit::updatePosition(float time)
{
    if (isMove)
    {
        sprite->setRotation((target - position).getAngle() * (-57) + initRotation);
        distanceToTarget = position.distance(target);
        Vec2 newPos = position;
        
        if (distanceToTarget > minDistance)
        {
            newPos += (speed * time * velocity);
            if (obstacles->getTileAt(Globals::get_instance()->positionToTileCoordinate(newPos)))
            {
                isMove = false;
                return;
            }

            sprite->setPosition(newPos);
            onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
            for (auto object : Globals::get_instance()->objects)
            {
                Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object->getPos());
                if (newPos != object->sprite->getPosition() && onMap == objOnmap)
                {
                    sprite->setPosition(position);
                    onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
                    target = mainLayer->getTileAt(onMap)->getBoundingBox().origin + Vec2(16, 16);
                    velocity = (target - position).getNormalized();
                    return;
                }
            }
            position = newPos;
        }
        else
        {
            isMove = false;
        }
    }
}

void MyUnit::updateSprite(float time)
{
    if (isMove)
    {
        if(runAnim->isDone())
        {
            runAnim->startWithTarget(sprite);
        }
        runAnim->step(time);
    }
    else
    {
        sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("s_w_torso_move_0004.tga")->getSpriteFrame());
    }
}

bool MyUnit::sendUnitInfoUDP()
{
    return true;
}
