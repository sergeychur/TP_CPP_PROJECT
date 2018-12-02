//
// Created by alex on 12.11.18.
//

#include "../include/AbstractServerNetObject.h"

void AbstractServerNetObject::set_parameters(std::string _ip, uint _port, size_t _player_num)
{
	ip = _ip;
	port = _port;
	player_num = _player_num;
}

AbstractServerNetObject::AbstractServerNetObject(uint _port, std::string _ip, size_t _player_num)
	:
	port(_port),
	ip(_ip),
	player_num(_player_num)
{

}
