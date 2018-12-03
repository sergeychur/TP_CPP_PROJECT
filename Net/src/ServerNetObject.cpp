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
	
	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append("endobj");
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

	send_buf.append(temp_buf); // write buf
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append("endobj");
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
	BOOST_LOG_TRIVIAL(info) << endpoint.address().to_string() << ' ' << endpoint.port() << std::endl;
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
		
		sock_mutex.lock(); // lock socket mutex
		if(socks[socks_index].socket->available()) {
			try {
				size_t message_length = 0;
				message_length =
					boost::asio::read_until(*(socks[socks_index].socket), boost::asio::dynamic_buffer(recv_buf), "endobj"); // read from socket
				sock_mutex.unlock(); // unlock socket mutex
				
				Serializable* serializable; // create pointer
				if(message_length < 9)
					throw std::invalid_argument("BAD INET MESSAGE");
				std::string type = recv_buf.substr(
					message_length - 9, TYPE_LENGTH); // read first N bytes to check which class object was sent
				recv_buf.erase(recv_buf.end() - 9, recv_buf.end());
				
				serializable = map[type]->create(); // create empty object
				
				// deserialize
				std::stringstream stream;
				recv_buf.resize(message_length - 9);
				stream << recv_buf;
				boost::archive::text_iarchive archive(stream);
	//			archive >> (*serializable);
				serializable->deserialize(archive);
				buf_mutex.lock();// lock buf mutex
				buf.push_back(serializable);// write to the buf
				buf_mutex.unlock(); // unlock buf mutex
			}
			catch(std::exception e)
			{
				BOOST_LOG_TRIVIAL(error) << e.what() << "RECV_BUF IS " << recv_buf << std::endl;
			}
		}
		else
			sock_mutex.unlock(); // unlock socket mutex
	}
	socks[socks_index].socket->close();
}


