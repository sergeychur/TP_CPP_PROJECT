//
// Created by alex on 17.12.18.
//

#include "../include/ClientNetObject.h"
#include "ClientNetObjectImpl.cpp"

ClientNetObject::ClientNetObject(
	std::string ip,
	uint port,
	std::map<std::string, DefaultAbstractFactory*> _map,
	std::string startobj_string = "STARTOBJ",
	std::string endobj_string = "ENDOBJ",
	size_t type_length = 3, int wait_time = 1)
{
	impl = new ClientNetObjectImpl(ip, port, _map,
		startobj_string,
		endobj_string,
		type_length, wait_time);
}

ClientNetObject::~ClientNetObject()
{
	delete impl;
}

void ClientNetObject::send(Serializable *serializable)
{
	impl->send(serializable);
}

std::vector<std::shared_ptr<Serializable>> ClientNetObject::receive()
{
	return impl->receive();
}

void ClientNetObject::work()
{
	impl->work();
}
