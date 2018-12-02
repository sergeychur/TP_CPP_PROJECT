//
// Created by alex on 12.11.18.
//

#include "ServerNetObject.h"


std::vector<std::shared_ptr<Serializable>> ServerNetObject::buf;

bool ServerNetObject::stop;

std::map<std::string,DefaultAbstractFactory*> ServerNetObject::map;

size_t ServerNetObject::player_num;

tcp::socket* ServerNetObject::socks; // REDO with separate objects consuming sock, thread and sock_mutex
std::mutex ServerNetObject::sock_mutex;
std::mutex ServerNetObject::buf_mutex;
std::mutex ServerNetObject::priority_buf_mutex;
std::mutex ServerNetObject::priority_sock_mutex;
boost::asio::io_context ServerNetObject::context;

tcp::socket ServerNetObject::connect() //return smth to send to recv func
{
	static tcp::acceptor acceptor(context,tcp::endpoint(tcp::v4(),port));
	return acceptor.accept();
}

void ServerNetObject::send(Serializable *serializable)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
	archive << serializable; // serialize
	std::string send_buf, temp_buf;
	stream >> temp_buf;
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(temp_buf); // write buf
	send_buf.append("endobj");
	priority_sock_mutex.lock(); // lock socket mutex
	sock_mutex.lock();
	for(int i = 0; i < player_num; ++i)
	{
		boost::asio::write(socks[i], boost::asio::buffer(send_buf)); // send
	}
	priority_sock_mutex.unlock(); // unlock socket mutex
	sock_mutex.unlock();
}

void ServerNetObject::send_to(Serializable *serializable, int i)
{
	std::stringstream stream;
	boost::archive::text_oarchive archive(stream);
	archive << serializable; // serialize
	std::string send_buf, temp_buf;
	stream >> temp_buf;
	send_buf.append(std::string(typeid(*serializable).name()).substr(0,TYPE_LENGTH)); // write object type
	send_buf.append(temp_buf); // write buf
	send_buf.append("endobj");
	priority_sock_mutex.lock(); // lock socket mutex
	sock_mutex.lock();
	boost::asio::write(socks[i], boost::asio::buffer(send_buf)); // send
	priority_sock_mutex.unlock(); // unlock socket mutex
	sock_mutex.unlock();
}

std::vector<std::shared_ptr<Serializable>> ServerNetObject::receive()
{
	priority_buf_mutex.lock(); // lock buf mutex
	buf_mutex.lock();
	auto temp=std::move(buf);
	buf.clear();
	priority_buf_mutex.unlock(); // unlock buf mutex
	buf_mutex.unlock();
	return temp;
}

ServerNetObject::ServerNetObject(uint _port, const std::string _ip, std::map<std::string,DefaultAbstractFactory*> _map)
	:
	port(_port),
	ip(_ip)
{
	map=std::move(_map);
	thread = nullptr;
	stop = false;
	player_num = 2;
}

void ServerNetObject::read_client_socks(const size_t thread_index)
{
	while(!stop)
	{
		std::string recv_buf;
		try_lock(priority_sock_mutex,sock_mutex); // lock socket mutex
		priority_sock_mutex.unlock();
		size_t message_length = 0;
		if(socks[thread_index].available())
			message_length = boost::asio::read_until(socks[thread_index], boost::asio::dynamic_buffer(recv_buf),"endobj"); // read from socket
		sock_mutex.unlock(); // unlock socket mutex
		
		recv_buf.erase(recv_buf.end()-6,recv_buf.end());
		
		std::shared_ptr<Serializable> serializable; // create pointer
		
		std::string type = recv_buf.substr(0,TYPE_LENGTH); // read first N bytes to check which class object was sent
		recv_buf.erase(0,TYPE_LENGTH);
		
		serializable = map[type]->create(); // create empty object
		
		// deserialize
		std::stringstream stream;
		stream << recv_buf;
		boost::archive::text_iarchive archive(stream);
		archive >> (*serializable);
		
		try_lock(priority_buf_mutex,buf_mutex);// lock buf mutex
		priority_buf_mutex.unlock();
		buf.push_back(serializable);// write to the buf
		buf_mutex.unlock(); // unlock buf mutex
	}
	socks[thread_index].close();
}

void ServerNetObject::work(size_t player_number = player_num)
{
	player_num = player_number;
	thread = new std::thread*[player_num];
	allocator.allocate(player_num); // REMOVE!
	for(size_t i = 0; i < player_num; ++i)
	{
		socks[i] = connect();
		thread[i] = new std::thread(read_client_socks, i);
	}
}

ServerNetObject::~ServerNetObject()
{
	if(thread) // check if work() was called
	{
		for(int i = 0; i < player_num; ++i)
		{
			stop=true; // set something to let threads know when to join
			thread[i]->join();
			delete thread[i];
			socks[i].~basic_stream_socket(); // REMOVE!
		}
		allocator.deallocate(socks, player_num); // REMOVE!
	}
	delete[] thread;
}
