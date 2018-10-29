//
// Created by alex on 09.10.18.
//

#include "ServerNetObject.h"

void ServerNetObject::set_player_number(short player_number)
{
    ServerNetObject::player_number = player_number;
}

void ServerNetObject::connect()
{

}

ServerNetObject::ServerNetObject(short player_number)
    : player_number(player_number)
{

}

void ServerNetObject::set_player(int port,std::string& ip)
{
    players.push_back(new NetObject(port,ip));
}

ServerNetObject::~ServerNetObject()
{
    while(!players.empty())
    {
        delete players[players.size()-1];
        players.pop_back();
    }
}

void ServerNetObject::send(Packet packet)
{

}

std::vector<Packet *> ServerNetObject::recieve()
{
    return std::vector<Packet *>();
}
