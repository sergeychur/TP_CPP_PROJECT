//
// Created by alex on 12.11.18.
//

#ifndef NET_NETOBJECT_H
#define NET_NETOBJECT_H


#include <vector>
#include "Serializable.h"

class NetObject
{
public:
	virtual void connect()=0;
	virtual void send(Serializable*)=0;
	virtual std::vector<Serializable*> receive()=0;
private:
	std::vector<Serializable*> buf;
};


#endif //NET_NETOBJECT_H
