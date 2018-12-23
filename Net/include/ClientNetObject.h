//
// Created by alex on 17.12.18.
//

#ifndef NET_CLIENTNETOBJECT_H
#define NET_CLIENTNETOBJECT_H

#include <map>
#include "AbstractClientNetObject.h"
#include "DefaultAbstractFactory.h"
#include "noncopyable.h"

class ClientNetObjectImpl;

class ClientNetObject : public AbstractClientNetObject, public noncopyable
{
public:
	ClientNetObject(std::string ip, uint port, std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length, int wait_time);
	~ClientNetObject();
	
	void send(Serializable *serializable) override;
	std::vector<std::shared_ptr<Serializable>> receive() override;
	void work() override;
	
private:
	ClientNetObjectImpl *impl;
};


#endif //NET_CLIENTNETOBJECT_H
