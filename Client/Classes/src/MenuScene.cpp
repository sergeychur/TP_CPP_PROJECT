//
//  MenuScene.cpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 27/10/2018.
//

#include "MenuScene.hpp"
#include "ui/CocosGUI.h"
Scene* MenuScene::createScene()
{

    auto scene = Scene::create();

    auto layer = MenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    auto gameScene = GameScene::createScene();
    auto startButton = ui::Button::create();
    startButton->setTitleText("Start Game");
    startButton->setPosition(Vec2(100, 100));
    startButton->addClickEventListener([&](Ref* sender){
        CCLOG("BAZ");
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(gameScene);
    });
    addChild(startButton);

    return true;
}

void MenuScene::update(float delta)
{

}
