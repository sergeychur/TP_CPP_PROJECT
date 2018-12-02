//
// Created by alex on 12.11.18.
//

#include <iostream>
#include "../include/ClientNetObject.h"

std::vector<std::unique_ptr<Serializable>> NetObject::buf;
std::map<std::string, DefaultAbstractFactory*> NetObject::map;

boost::asio::io_context ClientNetObject::context;
std::mutex ClientNetObject::priority_sock_mutex;
std::mutex ClientNetObject::priority_buf_mutex;
std::mutex ClientNetObject::sock_mutex;
std::mutex ClientNetObject::buf_mutex;

SubSock* ClientNetObject::sock;

bool SubSock::stop;

void ClientNetObject::send(Serializable *serializable)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
//	archive << serializable; // serialize
	serializable->serialize(archive);
	std::string send_buf, temp_buf;
//	stream >> temp_buf;
	temp_buf = stream.str();
	
	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append("endobj");
	priority_sock_mutex.lock(); // lock socket mutex
	sock_mutex.lock();
	boost::asio::write(*(sock->socket),boost::asio::buffer(send_buf)); // send
	priority_sock_mutex.unlock(); // unlock socket mutex
	sock_mutex.unlock();
}

std::vector<std::unique_ptr<Serializable>> ClientNetObject::receive()
{
	priority_buf_mutex.lock(); // lock buf mutex
	buf_mutex.lock();
	auto temp = std::move(buf);
	buf.clear();
	priority_buf_mutex.unlock(); // unlock buf mutex
	buf_mutex.unlock();
	return temp;
}

ClientNetObject::ClientNetObject(uint _port, std::string _ip, std::map<std::string,DefaultAbstractFactory*> _map)
	:
	AbstractClientNetObject(_port,_ip)
{
	map=std::move(_map);
	sock = nullptr;
}

void ClientNetObject::work()
{
	sock = new SubSock(context);
	connect();
	sock->thread = new std::thread(read_sock);
}

void ClientNetObject::connect()
{
	tcp::resolver resolver(context);
	boost::asio::connect(*(sock->socket), resolver.resolve(ip, std::to_string(port)));
//	boost::asio::connect(sock, tcp::endpoint(boost::asio::ip::address::from_string(ip),port));
}

ClientNetObject::~ClientNetObject()
{
	delete sock;
}

void ClientNetObject::read_sock()
{
	while(!(sock->stop))
	{
		std::string recv_buf;
		
		try_lock(sock_mutex, priority_sock_mutex); // lock socket mutex
		priority_sock_mutex.unlock();
		if(sock->socket->available())
		{
			size_t message_length = 0;
			message_length = boost::asio::read_until(*(sock->socket), boost::asio::dynamic_buffer(recv_buf),"endobj"); // read from socket
			sock_mutex.unlock(); // unlock socket mutex
			
			
			std::unique_ptr<Serializable> serializable; // create pointer
			
			std::string type = recv_buf.substr(message_length-9,TYPE_LENGTH); // read first N bytes to check which class object was sent
			recv_buf.erase(recv_buf.end()-9,recv_buf.end());
			
			serializable = map[type]->create(); // create empty object
			
			// deserialize
			std::stringstream stream;
			recv_buf.resize(message_length-9);
			stream << recv_buf;
			boost::archive::text_iarchive archive(stream);
//			archive >> (*serializable);
			serializable->deserialize(archive);
			try_lock(priority_buf_mutex,buf_mutex);// lock buf mutex
			priority_buf_mutex.unlock();
			buf.push_back(std::move(serializable));// write to the buf
			buf_mutex.unlock(); // unlock buf mutex
		}
		else
			sock_mutex.unlock();
	}
	sock->socket->close();
}
