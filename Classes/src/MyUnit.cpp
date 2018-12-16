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
    scheduleUpdate();
}


void MyUnit::onMouseDown(cocos2d::Event *event)
{
    CCLOG("CLICK ON                 ghhhhhhhhhhhh");
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
//        if (state == Move)
////        {
////            stopMoving();
////            isSelect = false;
////            startMoving();
////            sprite->setColor(Color3B::WHITE);
////            target = clickPos;
////            velocity = (target - position).getNormalized();
////        }
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
    std::vector<int> a = {hp , (int)position.x , (int)position.y , (int)sprite->getRotation()};
    Command com(Globals::get_instance()->player->id, id,"check", a);
    Globals::get_instance()->net->send(&com);
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
        sprite->setSpriteFrame(Sprite::createWithSpriteFrameName(DefaultSprite)->getSpriteFrame());
    }
}

void MyUnit::startMoving()
{
    std::vector<int> a = {(int)target.x , (int)target.y};
    Command com(Globals::get_instance()->player->id, id, "move", a);
    Globals::get_instance()->net->send(&com);
    mainLayer->getTileAt(onMap)->setColor(Color3B::WHITE);
    state = Move;

}

void MyUnit::stopMoving()
{
    std::vector<int> a = {};
    Command com(Globals::get_instance()->player->id, id, "pop_command", a);
    Globals::get_instance()->net->send(&com);
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
    for (auto& object : Globals::get_instance()->player->getUnits()) {
        Point checkOnmap = Globals::get_instance()->positionToTileCoordinate(checkPos);
        Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object.second->getPos());
        if (id != object.second->id && checkOnmap == objOnmap) {
            stopMoving();
            return true;
        }
    }

    for (auto& enemy : Globals::get_instance()->enemies)
    {
        for (auto& object : enemy.second->units)
        {
            CCLOG("%f %f", object.second->getPos().x, object.second->getPos().y);
            Point checkOnmap = Globals::get_instance()->positionToTileCoordinate(checkPos);
            Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object.second->getPos());
            CCLOG("%f %f", objOnmap.x, objOnmap.y);
            if (checkOnmap == objOnmap) {
                std::vector<int> a = {(int)enemy.second->id, (int)object.second->id};
                Command com(Globals::get_instance()->player->id, id,"kick", a);
                Globals::get_instance()->net->send(&com);
                stopMoving();
                state = Fight;
                return true;
            }
        }
    }
    return false;
}

void MyUnit::updateAttack(float time)
{

}

bool MyUnit::sendUnitInfoUDP()
{
    return true;
}
