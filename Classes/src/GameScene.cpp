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
    initNet();
    initGame();
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
        std::vector<Serializable*> rawInfo;
        rawInfo = net->receive();
        if (rawInfo.empty())
            return false;
        level = new Level();
        level->loadMap("TileMap.tmx");
        addChild(level->map);
        gameStarted = true;
        Initialiser info;
        info = *dynamic_cast<Initialiser *>(rawInfo[0]);
        player = new Player(info.player_id, Vec2(info.bases[info.player_id].first, info.bases[info.player_id].second));
        std::vector<int> a = {0 , 0 , 75 , 100};
        Command com(info.player_id, 0,"check", a);
        net->send(&com);
        CCLOG("player %d", info.player_id);
        for (int i = 0; i < info.player_num; ++i) {
            if (i != info.player_id)
            {
                auto enemy = new EnemyPlayer(i, Vec2(info.bases[i].first, info.bases[i].second));
                Globals::get_instance()->enemies[i] = enemy;
                level->map->addChild(enemy);
                CCLOG("player %d", i);
            }
        }
        level->map->addChild(player);
        Globals::get_instance()->player = player;
        auto obstacles = Globals::get_instance()->map->getLayer("Walls");
        if (obstacles)
            obstacles->setVisible(false);
        return true;
        delete rawInfo[0];
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
    std::vector<Serializable*> rawInfo;
    rawInfo = net->receive();
    if (rawInfo.empty())
        return;
    CCLOG("Got Info");
    for (int i = 0; i < rawInfo.size(); ++i)
    {
        Update info = *dynamic_cast<Update *>(rawInfo[i]);
        for (auto update : info.updates) {
            if (update.player_id == player->id)
            {
                CCLOG("Players unit");
                if (player->getUnits().empty())
                //if ( player->getUnits().find(update.unit_id) == player->getUnits().end())
                {
                    CCLOG("unit created");
                    player->getUnits()[update.unit_id] = new MyUnit(Vec2(update.new_x, update.new_y), update.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(player->getUnits()[update.unit_id]);
                }
//                else
//                {
//                    CCLOG("Players unit updated");
//                    player->getUnits()[update.unit_id]->position.x = update.new_x; //проверить элем
//                    player->getUnits()[update.unit_id]->position.y = update.new_y;
//                }
            } else
            {
                CCLOG("Enemy unit");
                auto enemy = Globals::get_instance()->enemies[update.player_id];
                if (enemy->units.empty())
                //if (enemy->units.find(update.unit_id) == enemy->units.end())
                {
                    CCLOG("unit enemy created");
                    enemy->units[update.unit_id] = new EnemyUnit(Vec2(update.new_x, update.new_y), update.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(enemy->units[update.unit_id]);
                }
                else
                {
                    CCLOG("unit enemy updated");
                    enemy->units[update.unit_id]->position.x = update.new_x; //проверить элем
                    enemy->units[update.unit_id]->position.y = update.new_y;
                    enemy->units[update.unit_id]->state = (GameObject::State)update.state;
                    CCLOG("%d", update.state);
                    enemy->units[update.unit_id]->sprite->setRotation(update.new_angle);
                }
            }
        }
        delete rawInfo[i];
    }

}

void GameScene::initGame()
{
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    auto startButton = ui::Button::create();
    startButton->setTitleText("Start Game");
    startButton->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    startButton->addClickEventListener([&](Ref* sender){
        CCLOG("Подключение сети");
        net->work();
        CCLOG("Сеть подключена");
        scheduleUpdate();
        removeChild(startButton);
        //delete(startButton);
    });
    addChild(startButton);
}

void GameScene::initNet()
{
    std::map<std::string,DefaultAbstractFactory*> map = {
            {std::string(typeid(Update).name()).substr(0,3), new UpdateFactory()},
            {std::string(typeid(Command).name()).substr(0,3), new CommandFactory()},
            {std::string(typeid(Initialiser).name()).substr(0,3), new InitialiserFactory()}
    };
    net = new ClientNetObject(50000, "10.42.0.1", map);
    Globals::get_instance()->net = net;
}
