//
// Created by alex on 12.11.18.
//

#ifndef NET_ABSTRACTCLIENTNETOBJECT_H
#define NET_ABSTRACTCLIENTNETOBJECT_H


#include "NetObject.h"

class AbstractClientNetObject : public NetObject
{
public:
	AbstractClientNetObject(uint _port, std::string _ip);
	void set_parameters(std::string _ip, uint _port);
protected:
	uint port;
	std::string ip;
};


#endif //NET_ABSTRACTCLIENTNETOBJECT_H
