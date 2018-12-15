//
// Created by alex on 12.11.18.
//

#ifndef NET_NETOBJECT_H
#define NET_NETOBJECT_H


#include <vector>
#include <boost/any.hpp>
#include <boost/log/trivial.hpp>
#include "Serializable.h"
#include "DefaultAbstractFactory.h"

const short TYPE_LENGTH=3;

class NetObject
{
public:
	virtual void send(Serializable*) = 0;
	virtual std::vector<Serializable*> receive() = 0;
	virtual void work() = 0;
	virtual ~NetObject() = default;
protected:
	static std::vector<Serializable*> buf;
	static std::map<std::string, DefaultAbstractFactory*> map;
};


#endif //NET_NETOBJECT_H
