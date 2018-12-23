//
// Created by alex on 17.12.18.
//

#ifndef NET_ABSTRACTNETOBJECT_H
#define NET_ABSTRACTNETOBJECT_H

#include "Serializable.h"

class AbstractNetObject
{
public:
	virtual void send(Serializable* serializable) = 0;
	virtual std::vector<std::shared_ptr<Serializable>> receive() = 0;
	virtual void work() = 0;
};


#endif //NET_ABSTRACTNETOBJECT_H
