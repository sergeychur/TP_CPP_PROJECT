//
// Created by alex on 29.10.18.
//

#ifndef NET_PACKET_H
#define NET_PACKET_H


class Packet
{
public:
    enum
    {
        Update,
        Command
    } data_type;
    template <typename T>
    void convert(T to_convert);
    
    template <typename T>
    T extract();
private:
    int* data;
};



#endif //NET_PACKET_H
