//
// Created by alex on 12.11.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include "AbstractServerNetObject.h"
#include "ClientNetObject.h"

class ServerNetObject:public AbstractServerNetObject
{
public:
	ServerNetObject(uint _port,const std::string& _ip);
	void send(Serializable *serializable) override;
	std::vector<std::shared_ptr<Serializable>> receive();
	void work(short player_number);
	~ServerNetObject();
private:
	
	void connect();
	static void read_client_socks();
	
	static std::vector<std::shared_ptr<Serializable>> buf;
	static bool stop;
	uint port;
	std::string ip;
	static short player_num;
	std::thread** thread;
};


#endif //NET_SERVERNETOBJECT_H
