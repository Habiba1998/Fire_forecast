#ifndef TCPCLIENT
#define TCPCLIENT
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.h"

class TCPClient: public Client
{
private: 
	int client_socket;								// The socket of client if it is connected
		 
		 
public:
	TCPClient();
	TCPClient(struct sockaddr_in address);
	bool connect_server(struct sockaddr_in address, bool accumulate = false);		// accumulate option to allow accumulating results
																					// To previous connection results
	void read_server();
	virtual ~TCPClient();
};
#endif

