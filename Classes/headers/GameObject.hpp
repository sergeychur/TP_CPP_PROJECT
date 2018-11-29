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
    explicit GameObject(Vec2 pos, bool isStatic = false, std::string plist = "warriorAnim.plist", std::string format = "s_w_torso_move_%04d.tga",
            int count = 23);
    Vector<SpriteFrame*> getAnimation(std::string format, int count);
    const Vec2& getPos();
    Sprite* sprite;
    Vec2 onMap;
    enum State { Move, Fight, Death};
    unsigned int id;
protected:
    Animate* runAnim;
    Animate* fightAnim;
    Animate* deathAnim;
    Vec2 position;
    Vec2 newPos;
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
private:
    void animationInit(Animate*& Anim, std::string plist, std::string format, int count);
    Vector<SpriteFrame *> frames;
};


#endif /* GameObject_hpp */
