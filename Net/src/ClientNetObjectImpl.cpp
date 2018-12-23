//
// Created by alex on 17.12.18.
//

#include <mutex>
#include "../include/AbstractClientNetObject.h"
#include "SubSock.cpp"
#include "../non_public_include/SerializationOperation.h"


class ClientNetObjectImpl : public AbstractClientNetObject
{
public:
	ClientNetObjectImpl(std::string _ip, uint _port, std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length, int wait_time)
		:
		serializer(_map,
			startobj_string,
			endobj_string,
			type_length),
		ip(_ip),
		port(_port),
		WAIT_TIME_BETWEEN_SEND(wait_time)
	{
		sock = nullptr;
	}
	
	~ClientNetObjectImpl()
	{
		delete sock;
	}
	
	void send(Serializable *serializable) override
	{
		std::string send_buf = serializer.serialize(serializable);
		
		static std::chrono::steady_clock::time_point send_time = std::chrono::steady_clock::now();
		while(std::chrono::steady_clock::now() < send_time + std::chrono::milliseconds(WAIT_TIME_BETWEEN_SEND))
			;
		send_time = std::chrono::steady_clock::now();
		
		sock_mutex.lock();
		boost::asio::write(*(sock->socket),boost::asio::buffer(send_buf)); // send
		sock_mutex.unlock();
	}
	
	std::vector<std::shared_ptr<Serializable>> receive() override
	{
		buf_mutex.lock();
		auto temp = std::move(buf);
		buf.clear();
		buf_mutex.unlock();
		return temp;
	}
	
	void work() override
	{
		sock = new SubSock(context);
		connect();
		tcp::no_delay option(true);
		sock->socket->set_option(option);
		sock->thread = new std::thread(std::bind(&ClientNetObjectImpl::read_sock, this));
	}
	
	void connect()
	{
		try
		{
			while(true)
			{
				tcp::resolver resolver(context);
				boost::system::error_code ec;
				boost::asio::connect(*(sock->socket), resolver.resolve(ip, std::to_string(port)), ec);
				if(!ec)
					break;
			}
		}
		catch(std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	
	void read_sock();
private:
	const SerializationOperation serializer;
	
	const std::string ip;
	const uint port;
	
	const int WAIT_TIME_BETWEEN_SEND;
	
	std::vector<std::shared_ptr<Serializable>> buf;
	
	boost::asio::io_context context;
	std::mutex sock_mutex;
	std::mutex buf_mutex;
	
	SubSock* sock;
};


void ClientNetObjectImpl::read_sock()
{
	std::string wrong_data_recv_buf; // in case of unsuccessful parse this will be used as a buf to prevent data loss
	while(!(sock->stop))
	{
		std::string temp_recv_buf;
		static std::string ENDOBJ = serializer.get_endobj();
		
		sock_mutex.lock(); // lock socket mutex
		
		if(sock->socket->available())
		{
			boost::asio::read_until(*(sock->socket), boost::asio::dynamic_buffer(temp_recv_buf), ENDOBJ); // read from socket
			sock_mutex.unlock(); // unlock socket mutex
			try
			{
				auto serializable = serializer.deserialize(wrong_data_recv_buf,temp_recv_buf);
				
				buf_mutex.lock(); // lock buf mutex
				buf.push_back(serializable); // write to the buf
				buf_mutex.unlock(); // unlock buf mutex
				
			}
			catch(std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
		{
			sock_mutex.unlock();
			if(!wrong_data_recv_buf.empty())
			{
				try
				{
					auto serializable = serializer.deserialize(wrong_data_recv_buf,temp_recv_buf);
					
					buf_mutex.lock(); // lock buf mutex
					buf.push_back(serializable); // write to the buf
					buf_mutex.unlock(); // unlock buf mutex
					
				}
				catch(std::invalid_argument& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
		}
	}
	sock->socket->close();
}
