//
// Created by alex on 23.11.18.
//

#ifndef NET_DEFAULTABSTRACTFACTORY_H
#define NET_DEFAULTABSTRACTFACTORY_H

#include "include/Serializable.h"
struct Update : Serializable
{
	void serialize(boost::archive::text_iarchive &ar, const unsigned int version) override
	{
	
	}
	
	void serialize(boost::archive::text_oarchive &ar, const unsigned int version) override
	{
	
	}
};

struct Command : Serializable
{
	void serialize(boost::archive::text_iarchive &ar, const unsigned int version) override
	{
	
	}
	
	void serialize(boost::archive::text_oarchive &ar, const unsigned int version) override
	{
	
	}
};

class DefaultAbstractFactory
{
public:
	virtual std::shared_ptr<Serializable> create() = 0;
};

class UpdateFactory : public DefaultAbstractFactory
{
public:
	std::shared_ptr<Serializable> create() override
	{
		return std::static_pointer_cast<Serializable>(std::make_shared<Update>());
	}
};

class CommandFactory : public DefaultAbstractFactory
{
public:
	std::shared_ptr<Serializable> create() override
	{
		return std::static_pointer_cast<Serializable>(std::make_shared<Command>());
	}
};


#endif //NET_DEFAULTABSTRACTFACTORY_H
