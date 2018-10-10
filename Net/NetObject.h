//
// Created by alex on 09.10.18.
//

#ifndef NET_NETOBJECT_H
#define NET_NETOBJECT_H



virtual class NetObject
{
public:
    virtual void connect() = 0;
protected:
    void send(void* data);
    void* receive();
};


#endif //NET_NETOBJECT_H
