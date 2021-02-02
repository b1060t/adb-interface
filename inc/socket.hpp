#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <utils.hpp>
#include <asio.hpp>

void test()
{
	asio::io_context io;
	asio::local::stream_protocol::endpoint fd("/data/testfd");
	asio::local::stream_protocol::socket socket(io);
	socket.connect(fd);
}

#endif