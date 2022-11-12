#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include "Sensor_node.h"
#include "Sensor.h"
#include <set>
#include <mutex>


class TCPServer: public Sensor_node
{
private:
	int server_socket;
	struct sockaddr_in address;

	bool handle_send(double reading, void* new_socket);
	void accept_connection();
public:
	
	TCPServer(Sensor* x, int port, unsigned int maxclients, int duration, sa_family_t f = AF_INET, in_addr_t a = INADDR_ANY);
	struct sockaddr_in get_address()
	{
		return address;
	}
	
	void run();
	virtual ~TCPServer();
};

#endif

