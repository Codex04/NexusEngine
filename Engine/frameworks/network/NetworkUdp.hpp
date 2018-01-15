//
// Made by Marco
//

#ifndef NETWORK_UDP_HPP_
# define NETWORK_UDP_HPP_

#include <unordered_map>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <thread>
#include <atomic>
#include <future>
#include <chrono>

#include "Nexus/errors/NetworkUdpException.hpp"
#include "ANetworkTransport.hpp"

#ifdef _WIN32
#include <ws2tcpip.h>
#include <dbnetlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif // _WIN32

#define MAX_BUFFER_SIZE 2048

void	__initSocket();
void	__closeSocket(int socket);
void	__stopSocket();

class NetworkUdp : public ANetworkTransport
{
protected:
	nx::Engine			*_engine;

	// Server variables
protected:
	struct sockaddr_in	_serverAddr;
	struct sockaddr_in 	_clientAddr;
	std::string         _ipS;
	short               _portS;
	char				_buff[MAX_BUFFER_SIZE];
	int                 _socketS;

	// Client variables
protected:
	struct addrinfo		*_addrInfo;
	std::string         _ipC;
	bool				_sendMode;
	short               _portC;
	int                 _socketC;

protected:
	// Server mode
	std::shared_ptr<std::thread>	_thReceive;

public:
	explicit	NetworkUdp(nx::Engine *engine);
	virtual		~NetworkUdp();

public:
	void		startSend(const std::string &ip, unsigned short port, std::vector<char> data);
	void		startReceive(unsigned short port);

public:
	void		send(std::vector<char> data);
	void		receive(unsigned short port);
};

#endif // NETWORK_UDP_HPP_
