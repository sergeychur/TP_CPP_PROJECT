//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_UPDATE_FACTORY_HPP
#define SERVER_UPDATE_FACTORY_HPP

#include "DefaultAbstractFactory.h"

class UpdateFactory : public DefaultAbstractFactory
{
public:
    std::unique_ptr<Serializable> create() override
    {
        return (std::make_unique<Update>());
    }
    ~UpdateFactory() override = default;
};



#endif //SERVER_UPDATE_FACTORY_HPP
