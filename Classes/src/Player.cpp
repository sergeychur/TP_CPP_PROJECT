//
//  Player.cpp
//  Lesson1 iOS
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "Player.hpp"
#include "Globals.h"
#include "MyBuilding.hpp"
#include "command.hpp"

Player::Player(size_t id, Vec2 pos) : spawnPoint(pos), id(id), unitsOffset(-50)
{
    auto eventListener = EventListenerMouse::create();
    eventListener->onMouseDown = CC_CALLBACK_1(Player::onMouseDown, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    auto mainLayer = Globals::get_instance()->map->getLayer("Background");
    auto mapPos = Globals::get_instance()->positionToTileCoordinate(spawnPoint);
    mainLayer->getTileAt(mapPos)->setColor(Color3B::RED);
    addUnit(spawnPoint.x - 100, spawnPoint.y);
}

void Player::addUnit(int x, int y)
{
    std::vector<int> a = {x , y , 75 , 100 , 1, 75, 1};
    Command com(this->id, 0,"create_unit", a);
    Globals::get_instance()->net->send(&com);
}

std::map<unsigned int, std::unique_ptr<GameObject>>& Player::getUnits()
{
    return units;
}

void Player::update(float delta)
{
    
}

void Player::onMouseDown(cocos2d::Event *event)
{

    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Point clickPos = Point(mouseEvent->getLocationInView().x,
                           Director::getInstance()->getWinSize().height + mouseEvent->getLocationInView().y);
    clickPos -= Globals::get_instance()->mapOffset;
    auto mapPos = Globals::get_instance()->positionToTileCoordinate(spawnPoint);
    auto mainLayer = Globals::get_instance()->map->getLayer("Background");
    CCLOG("CLICK ON                                                  BASE");
    if (mainLayer->getTileAt(mapPos)->getBoundingBox().containsPoint(clickPos))
    {CCLOG("CLICK ON                                                  BASE");
        CCLOG("CREATE UNIT");
        addUnit(spawnPoint.x, spawnPoint.y + unitsOffset);
        unitsOffset -= 50;
    }
}
