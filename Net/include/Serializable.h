//
// Created by alex on 12.11.18.
//

#ifndef NET_SERIALIZABLE_H
#define NET_SERIALIZABLE_H

#include <string>

struct Serializable
{
public:
	virtual std::string serialize()=0;
	virtual void deserialize(std::string)=0;
};


#endif //NET_SERIALIZABLE_H
