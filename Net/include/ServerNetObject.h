//
// Created by alex on 12.11.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include <thread>
#include <boost/asio.hpp>
#include "AbstractServerNetObject.h"
#include "../DefaultAbstractFactory.h"

using boost::asio::ip::tcp;

class ServerNetObject:public AbstractServerNetObject
{
public:
	// make it singleton
	ServerNetObject(uint _port, const std::string _ip, std::map<std::string,DefaultAbstractFactory*> _map);
	void send(Serializable *serializable) override;
	void send_to(Serializable *serializable, int i);
	std::vector<std::shared_ptr<Serializable>> receive();
	void work(short player_number);
	~ServerNetObject();
private:
	
	tcp::socket connect();
	static void read_client_socks(size_t thread_index);
	
	static std::vector<std::shared_ptr<Serializable>> buf;
	
	static bool stop;
	
	uint port;
	std::string ip;
	static std::map<std::string,DefaultAbstractFactory*> map;
	
	static short player_num;
	
	std::thread** thread;
	static tcp::socket* socks; // REDO with separate objects consuming sock, thread and sock_mutex
	static std::mutex sock_mutex;
	static std::mutex buf_mutex;
	static std::mutex priority_buf_mutex;
	static std::mutex priority_sock_mutex;
	static boost::asio::io_context context;
	std::allocator<tcp::socket> allocator; //delete later
};


#endif //NET_SERVERNETOBJECT_H
