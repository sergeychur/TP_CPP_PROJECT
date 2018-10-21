//
// Created by Сергей Апарин on 13.10.2018.
//

#ifndef TP_CPP_PROJECT_OBJECT_H
#define TP_CPP_PROJECT_OBJECT_H


#include <SFML/Graphics.hpp>
#include "Player.h"

class GameObject {
public:
    explicit GameObject();

    explicit GameObject(sf::RenderWindow &w, Player* player, std::string file, float width, float height, sf::Vector2f pos);

    virtual void drawObject();

 //   virtual void destroyObject();

    virtual void control(sf::Event event, sf::Vector2f cursor_pos) = 0;

  //  virtual void checkCollisionWithMap();

  //  virtual void attack();

    virtual void update(float time) = 0;

    virtual float getXcoord();

    virtual float getYcoord();

   // virtual ~GameObject();


protected:
    sf::RenderWindow &window;
    sf::Vector2f coordinates;
    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;
    Player *player;
    std::string File;
    float width;
    float height;
    bool isAlive{true};
    bool isMove{false};
    bool isSelect{false};

    float health;
    unsigned int id;

};


#endif //TP_CPP_PROJECT_OBJECT_H
