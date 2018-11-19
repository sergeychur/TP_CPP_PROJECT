//
// Created by alex on 12.11.18.
//

#include "ServerNetObject.h"

void ServerNetObject::connect()
{

}

void ServerNetObject::send(Serializable *serializable)
{

}

std::vector<Serializable *> ServerNetObject::receive()
{
	return nullptr;
}

void ServerNetObject::set_player_number(short player_number)
{
	ServerNetObject::player_number = player_number;
}

void ServerNetObject::set_ip(const std::string &ip)
{
	ServerNetObject::ip = ip;
}

void ServerNetObject::set_port(uint port)
{
	ServerNetObject::port = port;
}

ServerNetObject::ServerNetObject(uint _port, const std::string &_ip, short _player_number)
	:
	port(_port),
	ip(_ip),
	player_number(_player_number)
{

}
