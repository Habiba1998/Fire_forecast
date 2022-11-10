#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include "Sensor_node.h"
#include <set>


class TCPServer: public Sensor_node
{
private:
	int server_socket;
	struct sockaddr_in address;
	set<int> clients;				// set of clients connected to the server
	

public:
	
	TCPServer(int port, int maxclients, int duration, sa_family_t f = AF_INET, in_addr_t a = INADDR_ANY);
	struct sockaddr_in get_address()
	{
		return address;
	}
	int get_clients_number()
	{
		return clients.size();
	}
	void accept_connection();
	void handle_send(double reading);
	void run();
	virtual ~TCPServer();
};

#endif

