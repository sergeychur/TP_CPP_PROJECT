//
// Created by alex on 23.11.18.
//

#ifndef NET_DEFAULTABSTRACTFACTORY_H
#define NET_DEFAULTABSTRACTFACTORY_H

#include "Serializable.h"

class DefaultAbstractFactory
{
public:
	virtual std::shared_ptr<Serializable> create() = 0;
	virtual ~DefaultAbstractFactory() = default;
};


#endif //NET_DEFAULTABSTRACTFACTORY_H
