//
// Created by alex on 12.11.18.
//

#ifndef NET_SERVERNETOBJECT_H
#define NET_SERVERNETOBJECT_H


#include <thread>
#include <boost/asio.hpp>
#include "AbstractServerNetObject.h"
#include "DefaultAbstractFactory.h"
#include "SubSock.h"

using boost::asio::ip::tcp;

class ServerNetObject : public AbstractServerNetObject
{
public:
	// make it singleton
	ServerNetObject(uint _port, std::string _ip, size_t player_number, std::map<std::string,DefaultAbstractFactory*> _map);
	void send(Serializable *serializable) override;
	void send_to(Serializable *serializable, int i) override;
	std::vector<Serializable*> receive() override;
	void work() override;
	~ServerNetObject();
private:
	void connect(size_t);
	static void read_client_socks(size_t sub_sock_index);
//
	static boost::asio::io_context context;
	static std::mutex sock_mutex;
	static std::mutex buf_mutex;
	static std::string STARTOBJ;
	static std::string ENDOBJ;
	static SubSock* socks;
};


#endif //NET_SERVERNETOBJECT_H
