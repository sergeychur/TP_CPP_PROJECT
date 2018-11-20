//
// Created by alex on 12.11.18.
//

#include "../include/ServerNetObject.h"

void ServerNetObject::connect() //return smth to send to recv func
{

}

void ServerNetObject::send(Serializable *serializable)
{

}

std::vector<Serializable *> ServerNetObject::receive()
{
	//mutex take
	auto temp=buf;
	buf.clear();
	//mutex free
	return temp;
}

ServerNetObject::ServerNetObject(uint _port, const std::string &_ip)
	:
	port(_port),
	ip(_ip)
{
	stop=false;
	player_num=2;
}

void ServerNetObject::read_client_socks(/*smth*/)
{
	while(!stop)
	{
		;
	}
}

void ServerNetObject::work(short player_number=player_num)
{
	player_num=player_number;
	thread = new std::thread*[player_num];
	for(int i = 0; i < player_number; ++i)
	{
		connect(); // return smth
		thread[i]=new std::thread(read_client_socks/*,here goes connection*/);
	}
}

ServerNetObject::~ServerNetObject()
{
	for(int i = 0; i < player_num; ++i)
	{
		stop=true; //set something to let threads know when to join
		thread[i]->join();
		delete thread[i];
		
	}
	delete[] thread;
}
