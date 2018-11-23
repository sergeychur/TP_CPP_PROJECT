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
#include <iostream>
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
    scheduleUpdate();
    auto startButton = ui::Button::create();
    startButton->setTitleText("Start Game");
    startButton->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    startButton->addClickEventListener([&](Ref* sender){

        sendInitInfoToServer();
        removeAllChildren();
        level = new Level();
        level->loadMap("TileMap.tmx");
        player = new Player("ser", Vec2(200, 400));
        addChild(level);
        level->addChild(player);
//        enemies.push_back(new Player("Phillip", Vec2(700, 400)));
//        for(auto enemy : enemies)
//        {
//            level->addChild(enemy);
//        }
    });
    addChild(startButton);
    return true;
}

void GameScene::update(float delta)
{

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

GameScene::~GameScene()
{
}
