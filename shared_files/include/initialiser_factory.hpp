//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_INITIALISER_FACTORY_HPP
#define SERVER_INITIALISER_FACTORY_HPP

#include "DefaultAbstractFactory.h"
#include "initialiser.hpp"

class InitialiserFactory : public DefaultAbstractFactory
{
public:
    std::shared_ptr<Serializable> create() override
    {
        return (std::make_shared<Initialiser>());
    }
    ~InitialiserFactory() override = default;
};


#endif //SERVER_INITIALISER_FACTORY_HPP
