//
// Created by alex on 17.12.18.
//

#include "../include/ServerNetObject.h"
#include "ServerNetObjectImpl.cpp"

ServerNetObject::ServerNetObject(std::string ip,
	uint port,
	int player_num,
	std::map<std::string, DefaultAbstractFactory *> _map,
	std::string startobj_string = "STARTOBJ",
	std::string endobj_string = "ENDOBJ",
	size_t type_length = 3,
	int wait_time = 1)
{
	impl = new ServerNetObjectImpl(ip, port,
								   player_num, _map,
								   startobj_string, endobj_string,
								   type_length, wait_time);
}

ServerNetObject::~ServerNetObject()
{
	delete impl;
}

void ServerNetObject::send(Serializable *serializable, int player_number)
{
	impl->send(serializable, player_number);
}

void ServerNetObject::send(Serializable *serializable)
{
	impl->send(serializable);
}

std::vector<std::shared_ptr<Serializable>> ServerNetObject::receive()
{
	return impl->receive();
}

void ServerNetObject::work()
{
	impl->work();
}
