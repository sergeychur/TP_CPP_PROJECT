//
// Created by alex on 09.10.18.
//

#include "NetObject.h"

NetObject::NetObject()
{
    thread=new std::thread(read_sock);
}

NetObject::~NetObject()
{
    //need to set global variable to let thread know when to finish
    thread->join();
    delete thread;
}

void NetObject::read_sock()
{
    //read from the connection and write to recv_buf
}

Packet *NetObject::receive()
{
    return nullptr;
}

void NetObject::send(Packet packet)
{

}

NetObject::NetObject(int port,std::string& ip)
    :
    port(port),
    ip(ip)
{
    thread=new std::thread(read_sock);
}

void NetObject::set_port(int n_port)
{
    port=n_port;
}

void NetObject::connect()
{

}
