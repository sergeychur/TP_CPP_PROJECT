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
#include "EnemyPlayer.hpp"
#include "../../shared_files/include/initialiser.hpp"
#include "../../shared_files/include/update_factory.hpp"
#include "../../shared_files/include/command_factory.hpp"
#include "../../shared_files/include/initialiser_factory.hpp"
#include <vector>
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
    initNet();
    initGame();
    return true;
}

void GameScene::update(float delta)
{
    getInitInfoFromServer();
    dispatch();
    moveCamera(delta);
   // std::cerr << Globals::get_instance()->sendCheck << std::endl;
//    if (Globals::get_instance()->sendCheck)
//    {
//        std::vector<int> a = {0};
//        Command com(0, 0, "check", a);
//        Globals::get_instance()->net->send(&com);
//    }

}

bool GameScene::sendInitInfoToServer()
{

    return true;
}

bool GameScene::getInitInfoFromServer()
{
    if (!gameStarted) {
        std::vector<std::shared_ptr<Serializable>> rawInfo;
        rawInfo = net->receive();
        if (rawInfo.empty())
            return false;
        level = new Level();
        level->loadMap("TileMap.tmx");
        addChild(level->map);
        gameStarted = true;
        Initialiser info;
        info = *std::dynamic_pointer_cast<Initialiser>(rawInfo[0]);
        Globals::get_instance()->player =
                std::make_unique<Player>(info.player_id, Vec2(info.bases[info.player_id].first, info.bases[info.player_id].second));
        std::vector<int> a = {0 , 0 , 75 , 100};
        Command com(info.player_id, 0,"check", a);
        net->send(&com);
        for (int i = 0; i < info.player_num; ++i) {
            if (i != info.player_id)
            {
                Globals::get_instance()->enemies[i] = std::make_unique<EnemyPlayer>(i, Vec2(info.bases[i].first, info.bases[i].second));
                level->map->addChild(Globals::get_instance()->enemies[i].get());
                CCLOG("player %d", i);
            }
        }
        level->map->addChild(Globals::get_instance()->player.get());
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
    std::vector<std::shared_ptr<Serializable>> rawInfo;

    rawInfo = net->receive();
    if (rawInfo.empty())
        return;
    CCLOG("Got Info");
    for (int i = 0; i < rawInfo.size(); ++i)
    {
        Update info = *std::dynamic_pointer_cast<Update>(rawInfo[i]);;
        for (auto update : info.updates){
//            std::cout << update.new_x << " " << update.new_y << " " <<  update.new_angle << " " << update.state << "\n";
            if (update.player_id == Globals::get_instance()->player->id)
            {
                CCLOG("Players unit");
                if (Globals::get_instance()->player->getUnits().find(update.unit_id) == Globals::get_instance()->player->getUnits().end())
                {
                    CCLOG("unit created");
                    Globals::get_instance()->sendCheck = false;
                    Globals::get_instance()->player->getUnits()[update.unit_id] =
                            std::make_unique<MyUnit>(Vec2(update.new_x, update.new_y), update.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(Globals::get_instance()->player->getUnits()[update.unit_id].get());
                } else{
                    Globals::get_instance()->player->getUnits()[update.unit_id]->state = (GameObject::State)update.state;
                    Globals::get_instance()->player->getUnits()[update.unit_id]->hp = update.new_HP;
                    if (update.new_HP <= 0)
                    {
                        Globals::get_instance()->player->getUnits()[update.unit_id]->kill();
                        Globals::get_instance()->player->getUnits().erase(update.unit_id);
                    }
                }
            } else
            {
                CCLOG("Enemy unit");
                auto enemy = Globals::get_instance()->enemies[update.player_id].get();
                //if (enemy->units.empty())
                if (enemy->units.find(update.unit_id) == enemy->units.end())
                {
                    CCLOG("unit enemy created");
                    enemy->units[update.unit_id] = std::make_unique<EnemyUnit>(Vec2(update.new_x, update.new_y), update.unit_id, WarriorPlist ,WarriorFormat);
                    Globals::get_instance()->map->addChild(enemy->units[update.unit_id].get());
                }
                else
                {
                    CCLOG("unit enemy updated");
                    enemy->units[update.unit_id]->position.x = update.new_x; //проверить элем
                    enemy->units[update.unit_id]->position.y = update.new_y;
                    enemy->units[update.unit_id]->state = (GameObject::State)update.state;
                    CCLOG("        units         state         %d", update.state);
                    enemy->units[update.unit_id]->sprite->setRotation(update.new_angle);
                    enemy->units[update.unit_id]->hp = update.new_HP;
                    if (update.new_HP <= 0)
                    {
                        enemy->units[update.unit_id]->kill();
                        enemy->units.erase(update.unit_id);
                    }
                    CCLOG("        HP       %d", update.new_HP);
                }
            }
        }
    }

}

void GameScene::initGame()
{
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    auto startButton = ui::Button::create("Button-Free-PNG-Image.png");
    startButton->setScale(0.5);
    startButton->setTitleText("Start Game");
    startButton->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    startButton->addClickEventListener([&](Ref* sender){
        CCLOG("Подключение сети");
        net->work();
        CCLOG("Сеть подключена");
        scheduleUpdate();
        removeAllChildren();
    });
    auto bg = Sprite::create("BG.jpg");
    bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    addChild(bg, 0);
    addChild(startButton);
}

void GameScene::initNet()
{
    std::map<std::string,DefaultAbstractFactory*> map = {
            {std::string(typeid(Update).name()).substr(0,3), new UpdateFactory()},
            {std::string(typeid(Command).name()).substr(0,3), new CommandFactory()},
            {std::string(typeid(Initialiser).name()).substr(0,3), new InitialiserFactory()}
    };
    net = new ClientNetObject("172.20.10.7", 50000, map, "startobj", "endobj", 3, 1);
    Globals::get_instance()->net = net;
}
