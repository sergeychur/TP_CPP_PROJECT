//
// Created by alex on 12.11.18.
//

#ifndef NET_CLIENTNETOBJECT_H
#define NET_CLIENTNETOBJECT_H


#include <thread>
#include <mutex>
#include <boost/asio.hpp>

#include "AbstractClientNetObject.h"
#include "../DefaultAbstractFactory.h"

using boost::asio::ip::tcp;

class ClientNetObject:public AbstractClientNetObject
{
public:
	//make it singleton
	ClientNetObject(uint _port, std::string _ip, std::map<std::string, DefaultAbstractFactory*> _map);
	void send(Serializable *serializable) override;
	std::vector<std::shared_ptr<Serializable>> receive();
	void work();
	~ClientNetObject();
private:
	void connect();
	static void read_sock();
	static std::map<std::string, DefaultAbstractFactory*> map;
	static std::vector<std::shared_ptr<Serializable>> buf;
	static bool stop;
	uint port;
	std::string ip;
	std::thread* thread;
	
	static boost::asio::io_context context;
	static tcp::socket sock;
	static std::mutex priority_sock_mutex;
	static std::mutex priority_buf_mutex;
	static std::mutex sock_mutex;
	static std::mutex buf_mutex;
};


#endif //NET_CLIENTNETOBJECT_H
