//
// Created by Сергей Апарин on 20.10.2018.
//

#ifndef TP_CPP_PROJECT_PLAYER_H
#define TP_CPP_PROJECT_PLAYER_H


#include "Unit.h"

class Player {
public:
    Player();

    static void encode_udp();

    static void decode_udp();

    ~Player();

private:
    std::string nickName;
    bool isAlive;
    sf::Vector2f spawnPoint;
    std::vector<GameObject &> units;

};


#endif //TP_CPP_PROJECT_PLAYER_H
