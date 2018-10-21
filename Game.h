//
// Created by Сергей Апарин on 12.10.2018.
//

#ifndef TP_CPP_PROJECT_GAME_H
#define TP_CPP_PROJECT_GAME_H

#include "Level.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Game {
public:
    explicit Game(sf::RenderWindow &window);

    void menu();

    void start();

private:
    void gameInit();

    void gameLoop();

    void drawFrame();

  //  void connect();

 //   void disconnect();

  //  void listen_udp();

  //  void listen_tcp();

    bool online;
    sf::RenderWindow &window;
    Player* player;
    std::vector<Player*> enemyes;
    sf::UdpSocket socket_udp;
    sf::TcpSocket socket_tcp;
    std::string currentMap;
    Level map;

};


#endif //TP_CPP_PROJECT_GAME_H
