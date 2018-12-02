//
// Created by alex on 23.11.18.
//

#ifndef NET_DEFAULTABSTRACTFACTORY_H
#define NET_DEFAULTABSTRACTFACTORY_H

// #include "incluSerializable.h"

#include "update.hpp"
#include "command.hpp"
#include "initialiser.hpp"



class DefaultAbstractFactory
{
public:
	virtual std::unique_ptr<Serializable> create() = 0;
	virtual ~DefaultAbstractFactory() = default;
};

class UpdateFactory : public DefaultAbstractFactory
{
public:
	std::unique_ptr<Serializable> create() override
	{
		return (std::make_unique<Update>());
	}
	~UpdateFactory() override = default;
};

class CommandFactory : public DefaultAbstractFactory
{
public:
	std::unique_ptr<Serializable> create() override
	{
		return (std::make_unique<Command>());
	}
    ~CommandFactory() override = default;
};

class InitialiserFactory : public DefaultAbstractFactory
{
public:
    std::unique_ptr<Serializable> create() override
    {
        return (std::make_unique<Initialiser>());
    }
    ~InitialiserFactory() override = default;
};


#endif //NET_DEFAULTABSTRACTFACTORY_H
