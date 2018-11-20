//
// Created by alex on 12.11.18.
//

#include "../include/ClientNetObject.h"

void ClientNetObject::connect()
{

}

void ClientNetObject::send(Serializable *serializable)
{

}

std::vector<Serializable *> ClientNetObject::receive()
{
	//mutex take
	auto temp=buf;
	buf.clear();
	//mutex free
	return temp;
}

ClientNetObject::ClientNetObject(uint _port, std::string& _ip)
	:
	port(_port),
	ip(_ip)
{
	stop=false;
	thread=nullptr;
}

void ClientNetObject::work()
{
	connect();
	thread=new std::thread(read_sock);
}

ClientNetObject::~ClientNetObject()
{
	stop=true; //set something to let thread join
	thread->join();
	delete thread;
}

void ClientNetObject::read_sock()
{
	while(!stop)
	{
		; // read from socket
		// lock mutex
		// write to the buf
		// unlock mutex
	}
}
