//
// Created by alex on 12.11.18.
//

#include <iostream>
#include "../include/ClientNetObject.h"

std::vector<Serializable*> NetObject::buf;
std::map<std::string, DefaultAbstractFactory*> NetObject::map;

boost::asio::io_context ClientNetObject::context;
std::mutex ClientNetObject::sock_mutex;
std::mutex ClientNetObject::buf_mutex;

std::string ClientNetObject::STARTOBJ = "startobj";
std::string ClientNetObject::ENDOBJ = "endobj";

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
	send_buf.append(STARTOBJ);
	
	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(ENDOBJ);
	sock_mutex.lock();
	boost::asio::write(*(sock->socket),boost::asio::buffer(send_buf)); // send
	sock_mutex.unlock();
}

std::vector<Serializable*> ClientNetObject::receive()
{
	buf_mutex.lock();
	auto temp = std::move(buf);
	buf.clear();
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
	try {
		tcp::resolver resolver(context);
		boost::asio::connect(*(sock->socket), resolver.resolve(ip, std::to_string(port)));
//	boost::asio::connect(sock, tcp::endpoint(boost::asio::ip::address::from_string(ip),port));
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}
ClientNetObject::~ClientNetObject()
{
	delete sock;
}

void ClientNetObject::read_sock()
{
	std::string wrong_data_recv_buf; // in case of unsuccessful parse this will be used as a buf to prevent data loss
	while(!(sock->stop))
	{
		std::string temp_recv_buf, recv_buf;
		
		sock_mutex.lock(); // lock socket mutex
		
		if(sock->socket->available())
		{
			try
			{
				boost::asio::read_until(*(sock->socket), boost::asio::dynamic_buffer(temp_recv_buf), ENDOBJ); // read from socket
				
				sock_mutex.unlock(); // unlock socket mutex
				
				if(!wrong_data_recv_buf.empty())
					recv_buf.append(wrong_data_recv_buf);
				
				recv_buf.append(temp_recv_buf);
				
				size_t object_start;
				if((object_start = recv_buf.find(STARTOBJ)) == std::string::npos)
					throw std::invalid_argument("BAD INET MESSAGE: NO OBJECT START");
				
				size_t object_end;
				if((object_end = recv_buf.find(ENDOBJ, object_start)) == std::string::npos)
					throw std::invalid_argument("BAD INET MESSAGE: NO OBJECT END");
				
				std::string type = recv_buf.substr(
					object_end - TYPE_LENGTH, TYPE_LENGTH); // read first N bytes to check which class object was sent
				
				if(object_end + ENDOBJ.size() != recv_buf.size())
					wrong_data_recv_buf = recv_buf.substr(object_end);
				else
					wrong_data_recv_buf.clear();
				
				recv_buf.erase(object_end); // clear TYPE and ENDOBJ from message
				recv_buf.erase(0, object_start + STARTOBJ.size()); // clear STARTOBJ
				
				Serializable* serializable; // create pointer
				serializable = map[type]->create(); // create empty object
				
				// deserialize
				std::stringstream stream;
				stream << recv_buf;
				boost::archive::text_iarchive archive(stream);
				serializable->deserialize(archive);
				
				buf_mutex.lock();// lock buf mutex
				buf.push_back(serializable);// write to the buf
				buf_mutex.unlock(); // unlock buf mutex
			}
			catch(std::invalid_argument& e)
			{
				wrong_data_recv_buf.append(temp_recv_buf);
				std::cerr << e.what() << "RECV_BUF IS " << temp_recv_buf << std::endl;
			}
		}
		else
			sock_mutex.unlock();
	}
	sock->socket->close();
}
