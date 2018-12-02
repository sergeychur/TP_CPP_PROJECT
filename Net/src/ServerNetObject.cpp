//
// Created by alex on 12.11.18.
//

#include <iostream>
#include "../include/ServerNetObject.h"

std::vector<std::unique_ptr<Serializable>> NetObject::buf;
std::map<std::string, DefaultAbstractFactory*> NetObject::map;

boost::asio::io_context ServerNetObject::context;
std::mutex ServerNetObject::priority_sock_mutex;
std::mutex ServerNetObject::priority_buf_mutex;
std::mutex ServerNetObject::sock_mutex;
std::mutex ServerNetObject::buf_mutex;

SubSock* ServerNetObject::socks;

bool SubSock::stop;

void ServerNetObject::send(Serializable *serializable)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
	archive << serializable; // serialize
	std::string send_buf, temp_buf;
	stream >> temp_buf;
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(temp_buf); // write buf
	send_buf.append("endobj");
	priority_sock_mutex.lock(); // lock socket mutex
	sock_mutex.lock();
	for(int i = 0; i < player_num; ++i)
	{
		boost::asio::write(*(socks[i].socket), boost::asio::buffer(send_buf)); // send
	}
	priority_sock_mutex.unlock(); // unlock socket mutex
	sock_mutex.unlock();
}

void ServerNetObject::send_to(Serializable *serializable, int i)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
	archive << serializable; // serialize
	std::string send_buf, temp_buf;
	stream >> temp_buf;
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(temp_buf); // write buf
	send_buf.append("endobj");
	priority_sock_mutex.lock(); // lock socket mutex
	sock_mutex.lock();
	boost::asio::write(*(socks[i].socket), boost::asio::buffer(send_buf)); // send
	priority_sock_mutex.unlock(); // unlock socket mutex
	sock_mutex.unlock();
}

std::vector<std::unique_ptr<Serializable>> ServerNetObject::receive()
{
	priority_buf_mutex.lock(); // lock buf mutex
	buf_mutex.lock();
	auto temp=std::move(buf);
	buf.clear();
	priority_buf_mutex.unlock(); // unlock buf mutex
	buf_mutex.unlock();
	return temp;
}

ServerNetObject::ServerNetObject(uint _port, const std::string _ip, size_t _player_number, std::map<std::string,DefaultAbstractFactory*> _map)
	:
	AbstractServerNetObject(_port, _ip, _player_number)
{
	map = std::move(_map);
	socks = nullptr;
}

void ServerNetObject::connect(size_t socks_index) //return smth to send to recv func
{
	static tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),port));
	tcp::endpoint endpoint;
	acceptor.accept(*(socks[socks_index].socket), endpoint);
	std::cerr << endpoint.address() << endpoint.port() << std::endl;
}

void ServerNetObject::work()
{
	socks = new SubSock[player_num];
	for(size_t i = 0; i < player_num; ++i)
	{
		socks[i].socket = new tcp::socket(context);
		connect(i);
		socks[i].thread = new std::thread(read_client_socks, i);
	}
}

ServerNetObject::~ServerNetObject()
{
	delete[] socks;
}

void ServerNetObject::read_client_socks(const size_t socks_index)
{
	while(!(socks[socks_index].stop))
	{
		std::string recv_buf;
		try_lock(priority_sock_mutex,sock_mutex); // lock socket mutex
		priority_sock_mutex.unlock();
		if(socks[socks_index].socket->available())
		{
			boost::asio::read_until(*(socks[socks_index].socket), boost::asio::dynamic_buffer(recv_buf), "endobj"); // read from socket
			sock_mutex.unlock(); // unlock socket mutex
			
			recv_buf.erase(recv_buf.end() - 6, recv_buf.end());
			
			std::unique_ptr<Serializable> serializable; // create pointer
			
			std::string
				type = recv_buf.substr(0, TYPE_LENGTH); // read first N bytes to check which class object was sent
			recv_buf.erase(0, TYPE_LENGTH);
			
			serializable = map[type]->create(); // create empty object
			
			// deserialize
			std::stringstream stream;
			stream << recv_buf;
			boost::archive::text_iarchive archive(stream);
			archive >> (*serializable);
			
			try_lock(priority_buf_mutex, buf_mutex);// lock buf mutex
			priority_buf_mutex.unlock();
			buf.push_back(std::move(serializable));// write to the buf
			buf_mutex.unlock(); // unlock buf mutex
		}
	}
	socks[socks_index].socket->close();
}

