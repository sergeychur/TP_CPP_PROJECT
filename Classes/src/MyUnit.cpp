//
//  MyUnit.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//


#include "MyUnit.hpp"
#include "Globals.h"

MyUnit::MyUnit(Vec2 pos, unsigned int id) : GameObject(pos)
{
    GameObject::id = id;
    auto eventListener = EventListenerMouse::create();
    eventListener->onMouseDown = CC_CALLBACK_1(MyUnit::onMouseDown, this);
    onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, sprite);
    mainLayer = Globals::get_instance()->map->getLayer("Background");
    obstacles = Globals::get_instance()->map->getLayer("Walls");
    mainLayer->getTileAt(onMap)->setColor(Color3B::GREEN);
    setAnchorPoint(Globals::get_instance()->map->getAnchorPoint());
    if (obstacles)
        obstacles->setVisible(false);
    scheduleUpdate();
}


void MyUnit::onMouseDown(cocos2d::Event *event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Point clickPos = Point(mouseEvent->getLocationInView().x,
            Director::getInstance()->getWinSize().height + mouseEvent->getLocationInView().y);
    clickPos -= Globals::get_instance()->mapOffset;
    CCLOG("%f %f", sprite->getPosition().x, sprite->getPosition().y);
    //CCLOG("click %f %f", x, y);
    if (isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        isSelect = false;
        sprite->setColor(Color3B::WHITE);
    }
    if (!isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        Point onmap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
        if(mainLayer->getTileAt(onmap)->getBoundingBox().containsPoint(clickPos))
        {
            isSelect = true;
            sprite->setColor(Color3B::GREEN);
        }
    }
    if (isSelect && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        isSelect = false;
        startMoving();
        sprite->setColor(Color3B::WHITE);
        target = clickPos;
        velocity = (target - position).getNormalized();
    }
}

void MyUnit::update(float time)
{
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
                stopMoving();
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
            stopMoving();
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

void MyUnit::startMoving()
{
    mainLayer->getTileAt(onMap)->setColor(Color3B::WHITE);
    isMove = true;
}

void MyUnit::stopMoving()
{
    mainLayer->getTileAt(onMap)->setColor(Color3B::GREEN);
    isMove = false;
}

bool MyUnit::sendUnitInfoUDP()
{
    return true;
}
