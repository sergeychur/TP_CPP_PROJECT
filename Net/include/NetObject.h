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
	virtual void send(Serializable*)=0;
protected:
	static const short TYPE_LENGTH=3;
};


#endif //NET_NETOBJECT_H
