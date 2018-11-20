//
// Created by alex on 12.11.18.
//

#ifndef NET_CLIENTNETOBJECT_H
#define NET_CLIENTNETOBJECT_H


#include <thread>
#include "AbstractClientNetObject.h"

class ClientNetObject:public AbstractClientNetObject
{
public:
	//make it singleton
	ClientNetObject(uint _port, std::string& _ip);
	void send(Serializable *serializable) override;
	std::vector<Serializable *> receive() override;
	void work();
	~ClientNetObject();
private:
	static std::vector<Serializable*> buf;
	void connect() override;
	static void read_sock();
	static bool stop;
	uint port;
	std::string ip;
	std::thread* thread;
};


#endif //NET_CLIENTNETOBJECT_H
