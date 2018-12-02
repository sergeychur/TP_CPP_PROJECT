//
// Created by alex on 02.12.18.
//

#include "../include/SubSock.h"

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
