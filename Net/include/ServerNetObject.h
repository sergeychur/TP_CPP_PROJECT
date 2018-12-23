//
// Created by alex on 17.12.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include <map>
#include "AbstractServerNetObject.h"
#include "DefaultAbstractFactory.h"
#include "noncopyable.h"

class ServerNetObjectImpl;

class ServerNetObject : public AbstractServerNetObject, public noncopyable
{
public:
	ServerNetObject(std::string ip, uint port, int player_num, std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length, int wait_time);
	~ServerNetObject();
	
	void send(Serializable *serializable) override;
	std::vector<std::shared_ptr<Serializable>> receive() override;
	void work() override;
	void send(Serializable *serializable, int player_number) override;
private:
	ServerNetObjectImpl* impl;
};


#endif //NET_SERVERNETOBJECT_H
