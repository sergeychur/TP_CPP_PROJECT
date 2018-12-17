//
// Created by alex on 17.12.18.
//

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

SubSock::SubSock()
{
	thread = nullptr;
	stop = false;
}

SubSock::SubSock(boost::asio::io_context& context)
{
	socket = new tcp::socket(context);
	thread = nullptr;
	stop = false;
}

SubSock::~SubSock()
{
	stop = true;
	thread->join();
	delete socket;
	delete thread;
}