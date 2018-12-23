//
// Created by alex on 23.12.18.
//

#ifndef NET_SERIALIZATIONOPERATION_H
#define NET_SERIALIZATIONOPERATION_H

#include <string>
#include <map>
#include <iostream>

#include "DefaultAbstractFactory.h"

class SerializationOperation
{
public:
	SerializationOperation(std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length);
	
	std::string serialize(Serializable* serializable) const;
	std::shared_ptr<Serializable> deserialize(std::string& wrong_data_recv_buf, std::string& temp_recv_buf) const;
	std::string get_endobj() const;

private:
	std::map<std::string, DefaultAbstractFactory*> map;
	const std::string STARTOBJ;
	const std::string ENDOBJ;
	const size_t TYPE_LENGTH;
};


#endif //NET_SERIALIZATIONOPERATION_H
