//
// Created by alex on 12.11.18.
//

#include "ClientNetObject.h"

void ClientNetObject::connect()
{

}

void ClientNetObject::send(Serializable *serializable)
{

}

std::vector<Serializable *> ClientNetObject::receive()
{

}

ClientNetObject::ClientNetObject(uint _port, std::string& _ip)
	:
	port(_port),
	ip(_ip)
{
	thread=nullptr;
}

void ClientNetObject::work()
{
	connect();
	thread=new std::thread(read_sock);
}

ClientNetObject::~ClientNetObject()
{
	delete thread;
}

void ClientNetObject::read_sock()
{

}
