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
	ClientNetObject(uint _port, std::string& _ip);
	void send(Serializable *serializable) override;
	std::vector<Serializable *> receive() override;
	void work();
	~ClientNetObject();
private:
	void connect() override;
	static void read_sock();
	uint port;
	std::string ip;
	std::thread* thread;
};


#endif //NET_CLIENTNETOBJECT_H
