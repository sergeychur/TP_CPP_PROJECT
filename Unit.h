//
// Created by Сергей Апарин on 20.10.2018.
//

#ifndef TP_CPP_PROJECT_UNIT_H
#define TP_CPP_PROJECT_UNIT_H

#include "GameObject.h"
#include <cmath>

class Unit : public GameObject
{
public:
    explicit Unit(sf::RenderWindow &window, Player* player, std::string file, float w, float h, sf::Vector2f pos,
                        float speed);

    void control(sf::Event event, sf::Vector2f cursor_pos) override ;

   // virtual void checkCollisionWithMap(float Dx, float Dy);

  //  virtual void attack(GameObject &obj);

    void update(float time) override ;

    enum
    {
        left, right, up, down, stay
    }       state;

   // ~Unit();

protected:
    float speed;
    float attackRate;
    int dx;
    int dy;
    double tempX;
    double tempY;
    double distance = 0;//это расстояние от объекта до тыка курсора
    int direction;
};


#endif //TP_CPP_PROJECT_UNIT_H
