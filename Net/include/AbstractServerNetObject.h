//
// Created by alex on 12.11.18.
//

#ifndef NET_ABSTRACTSERVERNETOBJECT_H
#define NET_ABSTRACTSERVERNETOBJECT_H


#include "NetObject.h"

class AbstractServerNetObject : public NetObject
{
public:
	AbstractServerNetObject(uint _port, std::string _ip, size_t _player_num);
	virtual void set_parameters(std::string _ip, uint _port, size_t _player_num);
	virtual void send_to(Serializable *serializable, int i) = 0;
protected:
	uint port;
	std::string ip;
	size_t player_num;
};


#endif //NET_ABSTRACTSERVERNETOBJECT_H
