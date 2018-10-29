//
// Created by alex on 09.10.18.
//

#ifndef NET_NETOBJECT_H
#define NET_NETOBJECT_H

#include <thread>
#include "Packet.h"

class NetObject
{
public:
    NetObject();
    NetObject(int port, std::string& ip);
    NetObject(NetObject&)=delete;
    NetObject(NetObject&&)=delete;
    NetObject& operator=(NetObject&)=delete;
    NetObject& operator=(NetObject&&)=delete;
    ~NetObject();
    
    void set_port(int port);
    void send(Packet packet);
    Packet* receive();
    void connect();
protected:
    static short const BUF_SIZE=1024;
    static void read_sock();
    Packet recv_buf[BUF_SIZE];
private:
    int port;
    std::string ip;
    std::thread* thread;
};


#endif //NET_NETOBJECT_H
