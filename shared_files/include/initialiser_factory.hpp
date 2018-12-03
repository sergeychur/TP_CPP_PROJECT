//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_INITIALISER_FACTORY_HPP
#define SERVER_INITIALISER_FACTORY_HPP

#include "DefaultAbstractFactory.h"

class InitialiserFactory : public DefaultAbstractFactory
{
public:
    std::unique_ptr<Serializable> create() override
    {
        return (std::make_unique<Initialiser>());
    }
    ~InitialiserFactory() override = default;
};


#endif //SERVER_INITIALISER_FACTORY_HPP
