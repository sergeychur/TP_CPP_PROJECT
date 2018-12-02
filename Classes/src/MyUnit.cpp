//
//  MyUnit.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 24.10.2018.
//


#include "MyUnit.hpp"
#include "Globals.h"

MyUnit::MyUnit(Vec2 pos, unsigned int id, std::string plist, std::string format) : GameObject(pos, plist, format, 23)
{
    GameObject::id = id;
    auto eventListener = EventListenerMouse::create();
    eventListener->onMouseDown = CC_CALLBACK_1(MyUnit::onMouseDown, this);
    onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, sprite);
    mainLayer = Globals::get_instance()->map->getLayer("Background");
    obstacles = Globals::get_instance()->map->getLayer("Walls");
    mainLayer->getTileAt(onMap)->setColor(Color3B::GREEN);
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
    updateAttack(time);
}

void MyUnit::updatePosition(float time)
{
    if (state == Move)
    {
        sprite->setRotation((target - position).getAngle() * (-57) + initRotation);
        distanceToTarget = position.distance(target);
        newPos = position;
        
        if (distanceToTarget > minDistance)
        {
            newPos += (speed * time * velocity);
            Vec2 checkPos = newPos + (35 * speed * time * velocity);
            if (checkCollisionWithMap(checkPos))
            {
                return;
            }
            if (checkCollisionWithObject(checkPos))
            {
                return;
            }
            sprite->setPosition(newPos);
            onMap = Globals::get_instance()->positionToTileCoordinate(sprite->getPosition());
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
}

void MyUnit::startMoving()
{
    mainLayer->getTileAt(onMap)->setColor(Color3B::WHITE);
    state = Move;
}

void MyUnit::stopMoving()
{
    mainLayer->getTileAt(onMap)->setColor(Color3B::GREEN);
    state = None;
}

bool MyUnit::checkCollisionWithMap(Vec2 checkPos)
{
    if (obstacles->getTileAt(Globals::get_instance()->positionToTileCoordinate(checkPos)))
    {
        stopMoving();
        return true;
    }
    return false;
}

bool MyUnit::checkCollisionWithObject(Vec2 checkPos)
{
    for (auto object : Globals::get_instance()->player->getUnits()) {
        Point checkOnmap = Globals::get_instance()->positionToTileCoordinate(checkPos);
        Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object.second->getPos());
        if (id != object.second->id && checkOnmap == objOnmap) {
            stopMoving();
            return true;
        }
    }

    for (auto enemy : Globals::get_instance()->enemies)
    {
        for (auto object : enemy.second->units)
        {
            Point checkOnmap = Globals::get_instance()->positionToTileCoordinate(checkPos);
            Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object.second->getPos());
            if (id != object.second->id && checkOnmap == objOnmap) {
                stopMoving();
                attackedObj = object.second;
                state = Fight;
                return true;
            }
        }
    }
    return false;
}

void MyUnit::updateAttack(float time)
{
    //CCLOG("%d %d", hp, id);
    if (state == Move)
    {
        attackedObj = nullptr;
    }
    if (attackedObj && attackedObj->state == Move)
    {
        attackedObj = nullptr;
        state = None;
    }
    if (attackedObj != nullptr)
    {
        attackedObj->hp -= dmg * time;
    }
    if (attackedObj && attackedObj->hp <= 0)
    {
        attackedObj = nullptr;
        state = None;
    }
    if (hp <= 0)
    {
        mainLayer->getTileAt(onMap)->setColor(Color3B::WHITE);
        Globals::get_instance()->player->removeChild(this);
    }
}

bool MyUnit::sendUnitInfoUDP()
{
    return true;
}