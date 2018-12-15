//
// Created by alex on 12.11.18.
//

#include <iostream>
#include "../include/ServerNetObject.h"

std::vector<Serializable*> NetObject::buf;
std::map<std::string, DefaultAbstractFactory*> NetObject::map;

boost::asio::io_context ServerNetObject::context;
std::mutex ServerNetObject::sock_mutex;
std::mutex ServerNetObject::buf_mutex;
std::string ServerNetObject::STARTOBJ = "startobj";
std::string ServerNetObject::ENDOBJ = "endobj";

SubSock* ServerNetObject::socks;

bool SubSock::stop;

void ServerNetObject::send(Serializable *serializable)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);

//	archive << serializable; // serialize
	serializable->serialize(archive);
	
	std::string send_buf, temp_buf;
//	stream >> temp_buf;
//	std::cerr << stream.str();
	temp_buf = stream.str();
	send_buf.append(STARTOBJ);
	
	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(ENDOBJ);
	sock_mutex.lock();
	for(int i = 0; i < player_num; ++i)
	{
		boost::asio::write(*(socks[i].socket), boost::asio::buffer(send_buf)); // send
	}
	sock_mutex.unlock();
}

void ServerNetObject::send_to(Serializable *serializable, int i)
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
	boost::asio::write(*(socks[i].socket), boost::asio::buffer(send_buf)); // send
	sock_mutex.unlock();
}

std::vector<Serializable*> ServerNetObject::receive()
{
	buf_mutex.lock();
	auto temp=std::move(buf);
	buf.clear();
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
	std::cerr << endpoint.address() << ' ' << endpoint.port() << std::endl;
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
	std::string wrong_data_recv_buf; // in case of unsuccessful parse this will be used as a buf to prevent data loss
	while(!(socks[socks_index].stop))
	{
		std::string temp_recv_buf ,recv_buf;
		
		sock_mutex.lock(); // lock socket mutex
		
		if(socks[socks_index].socket->available())
		{
			boost::asio::read_until(*(socks[socks_index].socket), boost::asio::dynamic_buffer(temp_recv_buf), ENDOBJ); // read from socket
			sock_mutex.unlock(); // unlock socket mutex
			try
			{
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
			sock_mutex.unlock(); // unlock socket mutex
	}
	socks[socks_index].socket->close();
}


