//
// Created by alex on 17.12.18.
//

#include <mutex>
#include "../include/AbstractClientNetObject.h"
#include "SubSock.cpp"
#include "SerializationOperation.cpp"

class ClientNetObjectImpl;

void read_sock(ClientNetObjectImpl* impl);

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
		while(std::chrono::steady_clock::now() < send_time + std::chrono_literals::operator""ms(WAIT_TIME_BETWEEN_SEND))
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
		sock->thread = new std::thread(read_sock, this);
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
	
	friend void read_sock(ClientNetObjectImpl* impl);
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


void read_sock(ClientNetObjectImpl* impl)
{
	std::string wrong_data_recv_buf; // in case of unsuccessful parse this will be used as a buf to prevent data loss
	while(!(impl->sock->stop))
	{
		std::string temp_recv_buf;
		static std::string ENDOBJ = impl->serializer.get_endobj();
		
		impl->sock_mutex.lock(); // lock socket mutex
		
		if(impl->sock->socket->available())
		{
			boost::asio::read_until(*(impl->sock->socket), boost::asio::dynamic_buffer(temp_recv_buf), ENDOBJ); // read from socket
			impl->sock_mutex.unlock(); // unlock socket mutex
			auto serializable = impl->serializer.deserialize(wrong_data_recv_buf,temp_recv_buf);
			
			impl->buf_mutex.lock();// lock buf mutex
			impl->buf.push_back(serializable);// write to the buf
			impl->buf_mutex.unlock(); // unlock buf mutex
		}
		else
			impl->sock_mutex.unlock();
	}
	impl->sock->socket->close();
}
