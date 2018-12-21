//
// Created by sergey on 17.12.18.
//

#ifndef SERVER_SIDE_ADAPTER_HPP
#define SERVER_SIDE_ADAPTER_HPP

#include "server.hpp"
#include "ServerNetObject.h"

class Adapter : public Server {
 public:
	explicit Adapter(uint _port, std::string _ip, size_t player_number,
					 std::map<std::string, DefaultAbstractFactory *> _map) :
			server(std::make_unique<ServerNetObject>(_ip, _port, player_number, _map, "startobj", "endobj", 3, 1)) {}

	~Adapter() override = default;

	void work() override;

	void send_to(Serializable *, int) override;

	void send(Serializable *) override;

	std::vector<Command> receive() override;

 private:
	std::unique_ptr<ServerNetObject> server;
};

#endif		//  SERVER_SIDE_ADAPTER_HPP
