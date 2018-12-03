//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_COMMAND_FACTORY_HPP
#define SERVER_COMMAND_FACTORY_HPP

#include "DefaultAbstractFactory.h"



class CommandFactory : public DefaultAbstractFactory
{
public:
    std::unique_ptr<Serializable> create() override
    {
        return (std::make_unique<Command>());
    }
    ~CommandFactory() override = default;
};



#endif //SERVER_COMMAND_FACTORY_HPP
