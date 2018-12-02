//
// Created by alex on 12.11.18.
//

#ifndef NET_NETOBJECT_H
#define NET_NETOBJECT_H


#include <vector>
#include <boost/any.hpp>
#include "Serializable.h"
#include "DefaultAbstractFactory.h"

class NetObject : boost::noncopyable
{
public:
	virtual void send(Serializable*)=0;
	virtual std::vector<std::unique_ptr<Serializable>> receive() = 0;
	virtual void work() = 0;
	virtual ~NetObject() = default;
protected:
	static std::vector<std::unique_ptr<Serializable>> buf;
	static std::map<std::string, DefaultAbstractFactory*> map;
	static const short TYPE_LENGTH=3;
};


#endif //NET_NETOBJECT_H
