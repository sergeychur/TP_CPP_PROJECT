//
// Created by alex on 23.12.18.
//
#include <map>
#include "serialized_stub.h"
#include "../non_public_include/SerializationOperation.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


TEST(SerializationOperation, serialize_deserialize_stuff)
{
	const int TYPE_LENGTH = 3;
	std::map<std::string, DefaultAbstractFactory*> map;
	map.emplace(std::pair(std::string(typeid(Stuff).name()).substr(0, 3), new StuffFactory()));
	SerializationOperation serializer(map, "startobj", "endobj", TYPE_LENGTH);
	Stuff stuff;
	stuff.int_field = 4;
	stuff.bool_field = true;
	stuff.char_field = 'f';
	stuff.string_field = "abcd";
	stuff.vector_field.push_back(1);
	stuff.vector_field.push_back(2);
	stuff.vector_field.push_back(3);
	stuff.vector_field.push_back(5);
	std::string data = serializer.serialize(&stuff);
	std::string empty_string;
	empty_string.clear();
	auto deserialized_data = serializer.deserialize(empty_string, data);
	std::shared_ptr<Stuff> ptr = std::dynamic_pointer_cast<Stuff>(deserialized_data);
	EXPECT_EQ(stuff, *(ptr.get()));
	map.clear();
}
