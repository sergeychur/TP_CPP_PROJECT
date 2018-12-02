//
// Created by alex on 12.11.18.
//

#include "../include/AbstractClientNetObject.h"

void AbstractClientNetObject::set_parameters(std::string _ip, uint _port)
{
	ip = _ip;
	port = _port;
}

AbstractClientNetObject::AbstractClientNetObject(uint _port, std::string _ip)
	:
	port(_port),
	ip(_ip)
{

}
