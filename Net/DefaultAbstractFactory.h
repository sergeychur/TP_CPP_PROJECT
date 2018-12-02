//
// Created by alex on 23.11.18.
//

#ifndef NET_DEFAULTABSTRACTFACTORY_H
#define NET_DEFAULTABSTRACTFACTORY_H

#include "include/Serializable.h"

#include "../shared_files/include/update.hpp"
#include "../shared_files/include/command.hpp"
#include "../shared_files/include/initialiser.hpp"



class DefaultAbstractFactory
{
public:
	virtual std::shared_ptr<Serializable> create() = 0;
	virtual ~DefaultAbstractFactory() = default;
};

class UpdateFactory : public DefaultAbstractFactory
{
public:
	std::shared_ptr<Serializable> create() override
	{
		return std::static_pointer_cast<Serializable>(std::make_shared<Update>());
	}
	~UpdateFactory() override = default;
};

class CommandFactory : public DefaultAbstractFactory
{
public:
	std::shared_ptr<Serializable> create() override
	{
		return std::static_pointer_cast<Serializable>(std::make_shared<Command>());
	}
    ~CommandFactory() override = default;
};

class InitialiserFactory : public DefaultAbstractFactory
{
public:
    std::shared_ptr<Serializable> create() override
    {
        return std::static_pointer_cast<Serializable>(std::make_shared<Initialiser>());
    }
    ~InitialiserFactory() override = default;
};


#endif //NET_DEFAULTABSTRACTFACTORY_H
