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
#include "ui/CocosGUI.h"

using namespace cocos2d;


class GameObject : public Node
{
public:
    explicit GameObject(Vec2 pos,
            std::string plist,
            std::string format,
            int count = 23);
    Vector<SpriteFrame*> getAnimation(std::string format, int count);
    void kill();
    enum State { Move, Fight, Death, None};
    const Vec2& getPos();
    void setPos(Point);
    Sprite* sprite;
    Vec2 onMap;
    unsigned int id;
    int hp;
    int max_hp;
    int dmg;
    State state;
    Vec2 position;
    bool remoteFight;
    bool isAlive = true;
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
    ui::LoadingBar *loadingBar;
private:
    void animationInit(Animate*& Anim, std::string plist, std::string format, int count, bool);
    Vector<SpriteFrame *> frames;
};


#endif /* GameObject_hpp */
