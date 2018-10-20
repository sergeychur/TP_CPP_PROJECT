//
// Created by Сергей Апарин on 20.10.2018.
//

#ifndef TP_CPP_PROJECT_UNIT_H
#define TP_CPP_PROJECT_UNIT_H


#include "GameObject.h"

class Unit : public GameObject {
public:
    explicit Unit(sf::RenderWindow &w, std::vector<int> stats) : GameObject(w) {};

    void control();

    void checkCollisionWithMap(float Dx, float Dy);

    void attack(GameObject &obj);

    void update(float time);

    enum {
        left, right, up, down, stay
    } state;

    virtual ~Unit();

protected:
    float speed;
    float attackRate;
    int dx;
    int dy;
};


#endif //TP_CPP_PROJECT_UNIT_H
