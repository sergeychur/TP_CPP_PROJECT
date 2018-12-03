//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_COMMAND_FACTORY_HPP
#define SERVER_COMMAND_FACTORY_HPP

#include "DefaultAbstractFactory.h"



class CommandFactory : public DefaultAbstractFactory
{
public:
    Serializable* create() override
    {
        return (new Command());
    }
    ~CommandFactory() override = default;
};



#endif //SERVER_COMMAND_FACTORY_HPP
