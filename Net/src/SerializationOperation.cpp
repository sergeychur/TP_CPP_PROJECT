//
// Created by alex on 17.12.18.
//

#include <string>
#include <map>
#include <iostream>

#include "DefaultAbstractFactory.h"
#include "../non_public_include/SerializationOperation.h"

SerializationOperation::SerializationOperation(std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length)
		:
		map(_map),
		STARTOBJ(startobj_string),
		ENDOBJ(endobj_string),
		TYPE_LENGTH(type_length)
{

}

std::string SerializationOperation::serialize(Serializable* serializable) const
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
	serializable->serialize(archive);
	
	std::string send_buf, temp_buf;
	
	temp_buf = stream.str();
	send_buf.append(STARTOBJ);
	
	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(ENDOBJ);
	return send_buf;
}

std::shared_ptr<Serializable> SerializationOperation::deserialize(std::string& wrong_data_recv_buf, std::string& temp_recv_buf) const
{
	std::shared_ptr<Serializable> serializable; // create pointer
	try
	{
		std::string recv_buf;
		if(!wrong_data_recv_buf.empty())
			recv_buf.append(wrong_data_recv_buf);
		
		recv_buf.append(temp_recv_buf);
		
		size_t object_start;
		if((object_start = recv_buf.find(STARTOBJ)) == std::string::npos)
			throw std::invalid_argument("BAD INET MESSAGE: NO OBJECT START");
		
		size_t object_end;
		if((object_end = recv_buf.find(ENDOBJ, object_start)) == std::string::npos)
			throw std::invalid_argument("BAD INET MESSAGE: NO OBJECT END");
		
		std::string type = recv_buf.substr(
			object_end - TYPE_LENGTH, TYPE_LENGTH); // read first N bytes to check which class object was sent
		
		if(object_end + ENDOBJ.size() != recv_buf.size())
			wrong_data_recv_buf = recv_buf.substr(object_end);
		else
			wrong_data_recv_buf.clear();
		
		recv_buf.erase(object_end - TYPE_LENGTH); // clear TYPE and ENDOBJ from message
		recv_buf.erase(0, object_start + STARTOBJ.size()); // clear STARTOBJ
		
		
		
		
		serializable = map.at(type)->create(); // create empty object
		
		// deserialize
		std::stringstream stream;
		stream << recv_buf;
		boost::archive::text_iarchive archive(stream);
		serializable->deserialize(archive);
	}
	catch(std::invalid_argument& e)
	{
		wrong_data_recv_buf.append(temp_recv_buf);
		std::cerr << "RECV_BUF IS " << temp_recv_buf << std::endl;
		throw;
	}
	return serializable;
}

std::string SerializationOperation::get_endobj() const
{
	return ENDOBJ;
}
