//
//  MenuScene.hpp
//  MyGame-desktop
//
//  Created by Сергей Апарин on 27/10/2018.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include "cocos2d.h"
#include "GameScene.hpp"

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
    bool init() override ;
    CREATE_FUNC(MenuScene);
    static cocos2d::Scene* createScene();

private:
    void update(float time) override;

    
};

#endif /* MenuScene_hpp */
