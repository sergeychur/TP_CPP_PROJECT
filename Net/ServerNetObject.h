//
// Created by alex on 09.10.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include <vector>
#include "NetObject.h"

class ServerNetObject
{
public:
    explicit ServerNetObject(short player_number);
    void set_player_number(short player_number);
    void set_player(int port,std::string& ip);
    void connect();
    std::vector<Packet*> recieve();
    void send(Packet packet);
    ~ServerNetObject();
private:
    std::vector<NetObject*> players;
    short player_number;
};


#endif //NET_SERVERNETOBJECT_H
