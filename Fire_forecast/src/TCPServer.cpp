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


TCPServer::TCPServer(Sensor* x, int port, int maxclients, int duration, sa_family_t f, in_addr_t a) : Sensor_node(x, duration)
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
	int new_socket;
	int addrlen = sizeof(address);
	
	// The thread continues to execuye while the server is active
	while (active) {
		
		new_socket = accept(server_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen); 
		if (new_socket < 0 && active)
		{
			perror("Server Socket Accept Failed");
			exit(EXIT_FAILURE);
		}
		// Add the new accepted client_socket to list of clients
		else if (new_socket >=0 && active)
		{
			clients_mtx.lock();
			clients.insert(new_socket);
			clients_mtx.unlock();
			
		}
	}
}

// Function that sends the reading to the connected clients
void TCPServer::handle_send(double reading)
{
	
	int send_status;
	for (auto it = clients.begin(); it != clients.end();)
	{
		send_status =send(*it, &reading, sizeof(reading), MSG_NOSIGNAL);	// MSG_NOSIGNALto prevent terminating the process on failure

		// On failure to send, clear the client from the list as client closes the connection
		if (send_status < 0)
		{
			clients_mtx.lock();
			it = clients.erase(it);											// Update it with iterator next to the deleted item
			clients_mtx.unlock();

		}
		else
		{
			++it;
		}
		
	}
}

// Function to get the current number of connected clients using mutex locks
int TCPServer::get_clients_number()
{
	int size;
	clients_mtx.lock();
	size = clients.size();
	clients_mtx.unlock();
	return size;

}

// Function to instantiate two threads to handle server operations
// Thread coonection_thr: to accept new client connections, Thread send_thr: to send the sensor reading to the connected clients periodically
void TCPServer::run()
{
	std::thread connection_thr(&TCPServer::accept_connection, this);
	std::thread send_thr(&TCPServer::send_reading, this);
	connection_thr.detach();
	
	send_thr.detach();
}

TCPServer::~TCPServer()
{
	// Close server_socket
	active = false;
	shutdown(server_socket, SHUT_RDWR);
	close(server_socket);
}



