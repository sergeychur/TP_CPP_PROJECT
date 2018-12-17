//
// Created by alex on 17.12.18.
//

#ifndef NET_ABSTRACTSERVERNETOBJECT_H
#define NET_ABSTRACTSERVERNETOBJECT_H


#include "AbstractNetObject.h"

class AbstractServerNetObject :public AbstractNetObject
{
public:
	virtual void send(Serializable* serializable, int player_number) = 0;
};


#endif //NET_ABSTRACTSERVERNETOBJECT_H
