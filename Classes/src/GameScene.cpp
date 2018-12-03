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
#include "DefaultAbstractFactory.h"
#include "initialiser.hpp"
#include "EnemyPlayer.hpp"
//#include "ClientNetObject.h"

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
    std::map<std::string,DefaultAbstractFactory*> map = {
            {std::string(typeid(Update).name()).substr(0,3), new UpdateFactory()},
            {std::string(typeid(Command).name()).substr(0,3), new CommandFactory()},
            {std::string(typeid(Initialiser).name()).substr(0,3), new InitialiserFactory()}
        };
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    auto startButton = ui::Button::create();
    sendInitInfoToServer();
    startButton->setTitleText("Start Game");
    startButton->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    net = new ClientNetObject(50000, "10.42.0.1", map);
    Globals::get_instance()->net = net;
    startButton->addClickEventListener([&](Ref* sender){
        net->work();
        scheduleUpdate();
        //getInitInfoFromServer();
        CCLOG("Net.work");
        removeChild(startButton);
        //sendInitInfoToServer();
//        level = new Level();
//        level->loadMap("TileMap.tmx");
//        addChild(level->map);
//        player = new Player(0, Vec2(1200, 1200));
//        level->map->addChild(player);
//        Globals::get_instance()->player = player;
//        auto obstacles = Globals::get_instance()->map->getLayer("Walls");
//        if (obstacles)
//            obstacles->setVisible(false);
    });
    addChild(startButton);
    return true;
}

void GameScene::update(float delta)
{
    getInitInfoFromServer();
    dispatch();
    moveCamera(delta);

}

bool GameScene::sendInitInfoToServer()
{

    return true;
}

bool GameScene::getInitInfoFromServer()
{
    if (!gameStarted) {
        std::vector<std::unique_ptr<Serializable>> ini;
        ini = net->receive();
        if (ini.size() < 1)
            return false;
        gameStarted = true;
        Initialiser ini2;
        ini2 = *dynamic_cast<Initialiser *>(ini[0].get());
        level = new Level();
        level->loadMap("TileMap.tmx");
        addChild(level->map);
        player = new Player(ini2.player_id, Vec2(ini2.bases[ini2.player_id].first, ini2.bases[ini2.player_id].second));
        std::vector<int> a = {0 , 0 , 75 , 100};
        Command com(ini2.player_id, 0,"check", a);
        net->send(&com);
        CCLOG("player1 %d", ini2.player_id);
        for (int i = 0; i < ini2.player_num; ++i) {
            if (i != ini2.player_id)
            {
                auto enemy = new EnemyPlayer(i, Vec2(ini2.bases[i].first, ini2.bases[i].second));
                Globals::get_instance()->enemies[i] = enemy;
                level->map->addChild(enemy);
                CCLOG("player2 %d", i);
            }
        }
        level->map->addChild(player);
        Globals::get_instance()->player = player;
        auto obstacles = Globals::get_instance()->map->getLayer("Walls");
        if (obstacles)
            obstacles->setVisible(false);
        return true;
    }
    return false;
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

void GameScene::dispatch()
{
    std::vector<std::unique_ptr<Serializable>> ini;
    ini = net->receive();
    if (!ini.size())
        return;
    CCLOG("Got unit");
    for (int i = 0; i < ini.size(); ++i)
    {
        Update ini2 = *dynamic_cast<Update *>(ini[i].get());
        for (auto j : ini2.updates) {
            if (j.player_id == player->id)
            {
                CCLOG("Players unit");
                //if ( player->getUnits().find(j.unit_id) != player->getUnits().end())
                if (player->getUnits().empty())
                {
                    CCLOG("unit created");
                    player->getUnits()[j.unit_id] = new MyUnit(Vec2(j.new_x, j.new_y), j.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(player->getUnits()[j.unit_id]);

                }
                else
                {
                    player->getUnits()[j.unit_id]->position.x = j.new_x; //проверить элем
                    player->getUnits()[j.unit_id]->position.y = j.new_y;
                }
            } else
            {
                auto enemy = Globals::get_instance()->enemies[j.player_id];
                if (enemy->units.empty())
                {
                    CCLOG("unit enemy created");
                    enemy->units[j.unit_id] = new EnemyUnit(Vec2(j.new_x, j.new_y), j.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(enemy->units[j.unit_id]);

                }
                else
                {
                    player->getUnits()[j.unit_id]->position.x = j.new_x; //проверить элем
                    player->getUnits()[j.unit_id]->position.y = j.new_y;
                }
            }
        }
    }

}

void GameScene::initGame()
{
    removeAllChildren();
    level = new Level();
    level->loadMap("TileMap.tmx");
    addChild(level->map);
    player = new Player(0, Vec2(1200, 1200));
    level->map->addChild(player);
    Globals::get_instance()->player = player;
}
