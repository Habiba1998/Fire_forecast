//#include "..\stdafx.h"
//#include "..\include\TCPServer.h"
#include "TCPServer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Sensor.h"


TCPServer::TCPServer(Sensor* x, int port, unsigned int maxclients, int duration, sa_family_t f, in_addr_t a) : Sensor_node(x, duration)
{
	// Create socket for the server
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("Server Socket Creation Failed");
		exit(EXIT_FAILURE);
	}

	// Create address structure
	address.sin_family = f;
	address.sin_addr.s_addr = a;
	address.sin_port = htons(port);

	// Bind socket to the address
	if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("Server Socket Bind Failed");
		exit(EXIT_FAILURE);
	}

	// Make socket listen
	if (listen(server_socket, maxclients) < 0) {
		perror("Server Socket Listen Failed");
		exit(EXIT_FAILURE);
	}

	// Set active to true to mark that the server is active for the threads to execute
	active = true;
	

}

// Function that handles accepting new connection, it is handled by a thread
void TCPServer::accept_connection()
{
	struct sockaddr_storage serverStorage;
	int addrlen = sizeof(serverStorage);
	
	// The thread continues to execuye while the server is active
	while (active) {
		
		int* new_socket = new int;
		*new_socket = accept(server_socket, (struct sockaddr*)&serverStorage, (socklen_t*)&addrlen); 
		if (*new_socket < 0 && active)
		{
			perror("Server Socket Accept Failed");
			exit(EXIT_FAILURE);
		}
		// Add the new accepted client_socket to list of clients
		else if (*new_socket >=0 && active)
		{
			std::thread send_thr(&TCPServer::send_reading, this, (void*) new_socket);
			send_thr.detach();
			add_client();					// increment the number of clients
			
		}
	}
}

// Function that sends the reading to the connected clients
bool TCPServer::handle_send(double reading, void* new_socket)
{
	int send_status;
	send_status = send(*((int*) new_socket), &reading, sizeof(reading), MSG_NOSIGNAL);
	// On failure to send, return false
	if (send_status < 0)
	{
		remove_client();										// Decrement the number of clients
		close(*(int*)new_socket);
		delete (int*)new_socket;
		
		return false;
	}
	return true;
	
}



// Function to instantiate two threads to handle server operations
// Thread coonection_thr: to accept new client connections, Thread send_thr: to send the sensor reading to the connected clients periodically
void TCPServer::run()
{
	std::thread connection_thr(&TCPServer::accept_connection, this);
	connection_thr.detach();

}

TCPServer::~TCPServer()
{
	// Close server_socket
	active = false;
	shutdown(server_socket, SHUT_RDWR);
	close(server_socket);
}



