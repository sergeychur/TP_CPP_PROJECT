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


class GameObject : public Node
{
public:
    explicit GameObject(Vec2 pos,
            std::string plist,
            std::string format,
            int count = 23);
    Vector<SpriteFrame*> getAnimation(std::string format, int count);
    const Vec2& getPos();
    void setPos(Point);
    Sprite* sprite;
    Vec2 onMap;
    enum State { Move, Fight, Death, None};
    unsigned int id;
    GameObject* AttackedBy;
    GameObject* attackedObj;
    int hp;
    int dmg;
    State state;
    Vec2 position;
protected:
    Animate* runAnim;
    Animate* fightAnim;
    Animate* deathAnim;
    Vec2 newPos;
    int initRotation;
    int speed;
    Vec2 velocity;
    Vec2 target;
    float distanceToTarget;
    bool isSelect;
    unsigned int minDistance;
    TMXLayer *mainLayer;
    TMXLayer *obstacles;
private:
    void animationInit(Animate*& Anim, std::string plist, std::string format, int count, bool);
    Vector<SpriteFrame *> frames;
};


#endif /* GameObject_hpp */
