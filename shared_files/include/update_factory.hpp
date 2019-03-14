//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_UPDATE_FACTORY_HPP
#define SERVER_UPDATE_FACTORY_HPP

#include "DefaultAbstractFactory.h"
#include "update.hpp"

class UpdateFactory : public DefaultAbstractFactory {
 public:
	std::shared_ptr<Serializable> create() override {
		return (std::make_shared<Update>());
	}

	~UpdateFactory() override = default;
};


#endif 		//  SERVER_UPDATE_FACTORY_HPP
