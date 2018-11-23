//
//  GameObject.hpp
//  Lesson1 Mac
//
//  Created by Сергей Апарин on 22.10.2018.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include <string>
#include "cocos2d.h"
using namespace cocos2d;


class GameObject : public cocos2d::Node
{
public:
    GameObject(Vec2 pos, std::string plist, std::string format, int count);
    Vector<SpriteFrame*> getAnimation(std::string format, int count);
    const Vec2& getPos();
//    const Vec2& getOnMapPos();
//    const Sprite* getSprite();
    Sprite* sprite;
    Vec2 onMap;
    enum State { Move, Fight, Death};

protected:
    Animate* runAnim;
    Animate* fightAnim;
    Animate* deathAnim;
    Vec2 position;
    int initRotation;
    unsigned int speed;
    Vec2 velocity;
    unsigned int hp;
    Vec2 target;
    float distanceToTarget;
    bool isAlive;
    bool isSelect;
    bool isMove;
    unsigned int minDistance;
    TMXLayer *mainLayer;
    TMXLayer *obstacles;
    unsigned int id;
private:
    void animationInit(std::string plist, std::string format, int count);
    Vector<SpriteFrame *> frames;
};


#endif /* GameObject_hpp */
