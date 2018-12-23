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
    auto percent = (static_cast<double>(hp) / static_cast<double>(max_hp)) * 100;
    loadingBar->setPercent(percent);
   if (state != None) {
        std::vector<int> a = {hp, (int) position.x, (int) position.y, (int) sprite->getRotation()};
        Command com(Globals::get_instance()->player->id, id, "check", a);
        Globals::get_instance()->net->send(&com);
   }
}

void MyUnit::updatePosition(float time)
{
    //if (state == Move || state == None)
    {
        sprite->setRotation((target - position).getAngle() * (-57) + initRotation);
        distanceToTarget = position.distance(target);
        newPos = position;
        
        if (distanceToTarget > minDistance)
        {
            newPos += (speed * time * velocity);
            Vec2 checkPos = newPos + (30 * speed * time * velocity);
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
        else if (state == Move)
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
    else if (state == Fight || remoteFight)
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
    CCLOG("POP    COMMAND    SENT");
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
            Point checkOnmap = Globals::get_instance()->positionToTileCoordinate(checkPos);
            Point objOnmap = Globals::get_instance()->positionToTileCoordinate(object.second->getPos());
            if (onMap == (objOnmap + Point(0, 1)) || onMap == (objOnmap + Point(0, -1)) || onMap == (objOnmap + Point(1, 0)) || onMap == (objOnmap + Point(-1, 0)) || onMap == (objOnmap + Point(1, 1)) ||onMap == (objOnmap + Point(-1, -1)) || onMap == (objOnmap + Point(1, -1)) || onMap == (objOnmap + Point(-1, 1))) {
                attackedPlayer = (int)enemy.second->id;
                attackedUnit = (int)object.second->id;
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
    if (state == Fight)
    {
        std::vector<int> a = {attackedPlayer, attackedUnit};
        Command com(Globals::get_instance()->player->id, id,"kick", a);
        Globals::get_instance()->net->send(&com);
    }
}

bool MyUnit::sendUnitInfoUDP()
{
    return true;
}
