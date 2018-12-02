//
// Created by alex on 12.11.18.
//

#ifndef NET_SERIALIZABLE_H
#define NET_SERIALIZABLE_H

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct Serializable
{
public:
	virtual void serialize(boost::archive::text_oarchive& ar) = 0;
	
	virtual void deserialize(boost::archive::text_iarchive& ar) = 0;
//	virtual void serialize(boost::archive::text_iarchive& ar, const unsigned int version) = 0;
//	virtual void serialize(boost::archive::text_oarchive& ar, const unsigned int version) = 0;
	virtual ~Serializable() = default;
};


#endif //NET_SERIALIZABLE_H
