//
// Created by alex on 12.11.18.
//

#ifndef NET_CLIENTNETOBJECT_H
#define NET_CLIENTNETOBJECT_H


#include <thread>
#include <mutex>
#include <boost/asio.hpp>

#include "AbstractClientNetObject.h"
#include "DefaultAbstractFactory.h"
#include "SubSock.h"

using boost::asio::ip::tcp;

class ClientNetObject : public AbstractClientNetObject
{
public:
//	//make it singleton
	ClientNetObject(uint _port, std::string _ip, std::map<std::string, DefaultAbstractFactory*> _map);
	void send(Serializable *serializable) override;
	std::vector<Serializable*> receive();
	void work() override;
	~ClientNetObject();
private:
	void connect();
	static void read_sock();
	
	static boost::asio::io_context context;
	static std::mutex sock_mutex;
	static std::mutex buf_mutex;
	
	static SubSock* sock;
};


#endif //NET_CLIENTNETOBJECT_H
