//
//  GameScene.hpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "Level.hpp"
#include "Player.hpp"
#include "EnemyPlayer.hpp"
#include "ui/CocosGUI.h"
#include <vector>
#include <map>


class GameScene : public cocos2d::Layer
{
public:
    //CONSTRUCTOR & METHODS
    bool init() override ;
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    Scene scene;
    ~GameScene();
private:
    Level* level;
    Player* player;
    std::map<unsigned int, EnemyPlayer*> enemies;
    //std::vector<GameObject*> units;
    std::vector<EventKeyboard::KeyCode> heldKeys;
    bool gameStarted;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override ;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override ;
    bool sendInitInfoToServer();
    bool getInitInfoFromServer();
    void moveCamera(float delta);
    void update(float time) override;
};

#endif /* GameScene_hpp */
