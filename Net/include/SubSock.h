//
// Created by alex on 02.12.18.
//

#ifndef NET_SUBSOCK_H
#define NET_SUBSOCK_H

#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct SubSock
{
	SubSock();
	explicit SubSock(boost::asio::io_context& context);
	std::thread* thread;
	tcp::socket* socket;
	bool stop;
	~SubSock();
};



#endif //NET_SUBSOCK_H
