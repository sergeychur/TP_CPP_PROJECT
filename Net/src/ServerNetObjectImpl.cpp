//
// Created by alex on 17.12.18.
//

#include <mutex>
#include "../include/AbstractServerNetObject.h"
#include "SubSock.cpp"
#include "../non_public_include/SerializationOperation.h"


class ServerNetObjectImpl : public AbstractServerNetObject
{
public:
//	friend void read_client_socks(ServerNetObjectImpl* impl, int socks_index);
	
	ServerNetObjectImpl(std::string _ip, uint _port, int player_number, std::map<std::string, DefaultAbstractFactory*> _map,
		std::string startobj_string,
		std::string endobj_string,
		size_t type_length, int wait_time)
		:
		serializer(_map,
				   startobj_string,
				   endobj_string,
				   type_length),
		player_num(player_number),
		ip(_ip),
		port(_port),
		WAIT_TIME_BETWEEN_SEND(wait_time)
	{
		socks = nullptr;
	}
	
	~ServerNetObjectImpl()
	{
		delete[] socks;
	}
	
	void send(Serializable *serializable) override
	{
		std::string send_buf = serializer.serialize(serializable);
		
		static std::chrono::steady_clock::time_point send_time = std::chrono::steady_clock::now();
		while(std::chrono::steady_clock::now() < send_time + std::chrono::milliseconds(WAIT_TIME_BETWEEN_SEND))
			;
		send_time = std::chrono::steady_clock::now();
		
		sock_mutex.lock();
		for(int i = 0; i < player_num; ++i)
		{
			boost::asio::write(*(socks[i].socket), boost::asio::buffer(send_buf)); // send
		}
		sock_mutex.unlock();
	}
	
	void read_client_socks(int socks_index);
	
	void send(Serializable *serializable, int player_number) override
	{
		std::string send_buf = serializer.serialize(serializable);
		
		sock_mutex.lock();
		boost::asio::write(*(socks[player_number].socket), boost::asio::buffer(send_buf)); // send
		sock_mutex.unlock();
	}
	
	std::vector<std::shared_ptr<Serializable>> receive() override
	{
		buf_mutex.lock();
		auto temp=std::move(buf);
		buf.clear();
		buf_mutex.unlock();
		return temp;
	}
	
	void work() override
	{
		socks = new SubSock[player_num];
		for(size_t i = 0; i < player_num; ++i)
		{
			socks[i].socket = new tcp::socket(context);
			connect(i);
			tcp::no_delay option(true);
			socks[i].socket->set_option(option);
			socks[i].thread = new std::thread(std::bind(&ServerNetObjectImpl::read_client_socks, this, i));
		}
	}
	
	void connect(size_t socks_index)
	{
		static tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),port));
		tcp::endpoint endpoint;
		acceptor.accept(*(socks[socks_index].socket), endpoint);
		std::cerr << endpoint.address() << ' ' << endpoint.port() << std::endl;
	}
	
private:
	
	
	const SerializationOperation serializer;
	
	const int player_num;
	
	const std::string ip;
	const uint port;
	
	const int WAIT_TIME_BETWEEN_SEND;
	
	boost::asio::io_context context;
	std::mutex sock_mutex;
	std::mutex buf_mutex;
	SubSock* socks; // TODO(Me): unordered_map
	
	
	std::vector<std::shared_ptr<Serializable>> buf;
};

void ServerNetObjectImpl::read_client_socks(int socks_index)
{
	std::string wrong_data_recv_buf; // in case of unsuccessful parse this will be used as a buf to prevent data loss
	while(!(socks[socks_index].stop))
	{
		std::string temp_recv_buf;
		static std::string ENDOBJ = serializer.get_endobj();
		sock_mutex.lock(); // lock socket mutex
		
		if(socks[socks_index].socket->available())
		{
			boost::asio::read_until(*(socks[socks_index].socket), boost::asio::dynamic_buffer(temp_recv_buf), ENDOBJ); // read from socket
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
			sock_mutex.unlock(); // unlock socket mutex
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
	socks[socks_index].socket->close();
}
