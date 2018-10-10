//
// Created by alex on 09.10.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include <queue>
#include "NetObject.h"

class ServerNetObject: public NetObject
{
public:
    void set_player_num();
    void send(Update update);
    std::vector<std::queue<Command>> receive_all();
private:
    std::queue<Command> receive();
    void* update_to_data(Update);
    std::queue<Command> data_to_command_queue();
    short player_number;
};


#endif //NET_SERVERNETOBJECT_H
