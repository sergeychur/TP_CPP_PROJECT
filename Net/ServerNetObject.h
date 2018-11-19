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
	ServerNetObject(uint _port=50000,const std::string& _ip, short _player_number);
	void connect() override;
	void send(Serializable *serializable) override;
	std::vector<Serializable *> receive() override;
	
	void set_player_number(short player_number);
	void set_ip(const std::string &ip);
	void set_port(uint port);
private:
	uint port;
	std::string ip;
	short player_number;
	std::vector<AbstractClientNetObject> players;
};


#endif //NET_SERVERNETOBJECT_H
