//
//  GameScene.cpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#include "GameScene.hpp"
#include "MyUnit.hpp"
#include "EnemyUnit.hpp"
#include "Globals.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    scheduleUpdate();
    auto startButton = ui::Button::create();
    startButton->setTitleText("Start Game");

    startButton->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    startButton->addClickEventListener([&](Ref* sender){
        sendInitInfoToServer();
        removeAllChildren();
        level = new Level();
        level->loadMap("TileMap.tmx");
        addChild(level->map);
        player = new Player("ser", Vec2(1200, 1200));
        level->map->addChild(player);
        Globals::get_instance()->player = player;
        CCLOG("%f %f", Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    });
    addChild(startButton);
    return true;
}

void GameScene::update(float delta)
{

    moveCamera(delta);
    if (Globals::get_instance()->requiredPlayersCount == enemies.size())
    {
        level->addChild(player);
    }
    else
    {
        getInitInfoFromServer();
    }
}

bool GameScene::sendInitInfoToServer()
{
    return true;
}

bool GameScene::getInitInfoFromServer() {
    return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()){
        heldKeys.push_back(keyCode);
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

void GameScene::moveCamera(float delta)
{
    if(std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end())
    {
        Globals::get_instance()->mapOffset.x -= Globals::get_instance()->mapMoveSpeed * delta;
        level->map->setPosition(Globals::get_instance()->mapOffset);
    }
    if(std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end())
    {
        Globals::get_instance()->mapOffset.x += Globals::get_instance()->mapMoveSpeed * delta;
        level->map->setPosition(Globals::get_instance()->mapOffset);
    }
    if(std::find(heldKeys.begin(), heldKeys.end(), DOWN_ARROW) != heldKeys.end())
    {
        Globals::get_instance()->mapOffset.y += Globals::get_instance()->mapMoveSpeed * delta;
        level->map->setPosition(Globals::get_instance()->mapOffset);
    }
    if(std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end())
    {
        Globals::get_instance()->mapOffset.y -= Globals::get_instance()->mapMoveSpeed * delta;
        level->map->setPosition(Globals::get_instance()->mapOffset);
    }
}
GameScene::~GameScene()
{
}