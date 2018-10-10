//
// Created by alex on 09.10.18.
//

#ifndef NET_CLIENTNETOBJECT_H
#define NET_CLIENTNETOBJECT_H


#include <queue>
#include "NetObject.h"

class ClientNetObject: public NetObject
{
public:
    void send(std::queue<Command> commands);
    Update receive();
private:
    void* command_queue_to_data(std::queue);
    Update data_to_update();
};


#endif //NET_CLIENTNETOBJECT_H
