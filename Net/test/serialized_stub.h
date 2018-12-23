//
// Created by alex on 23.12.18.
//

#ifndef NET_SERIALIZED_STUB_H
#define NET_SERIALIZED_STUB_H

#include "DefaultAbstractFactory.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>


struct Stuff : public Serializable
{
	int int_field;
	char char_field;
	bool bool_field;
	std::string string_field;
	std::vector<int> vector_field;
	
	void serialize(boost::archive::text_oarchive& ar)
	{
		ar & int_field;
		ar & char_field;
		ar & bool_field;
		ar & string_field;
		ar & vector_field;
	}
	
	void deserialize(boost::archive::text_iarchive& ar)
	{
		ar & int_field;
		ar & char_field;
		ar & bool_field;
		ar & string_field;
		ar & vector_field;
	}
	bool operator==(const Stuff other) const
	{
		return
			 other.int_field == int_field &&
			 other.char_field == char_field &&
			 other.bool_field == bool_field &&
			 other.string_field == string_field &&
			 other.vector_field == vector_field;
	}
};

class StuffFactory : public DefaultAbstractFactory
{
public:
	std::shared_ptr<Serializable> create()
	{
		return std::make_shared<Stuff>();
	}
	~StuffFactory() = default;
};


#endif //NET_SERIALIZED_STUB_H
