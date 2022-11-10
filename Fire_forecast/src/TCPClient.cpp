//#include "stdafx.h"
//#include "..\include\TCPClient.h"
#include "TCPClient.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <cerrno>
#include <thread>
#define timeout_sec 5
#define timeout_u_sec 0

TCPClient::TCPClient()
{
	connected = false;
	
}

// Function to connect client to server of given address
bool TCPClient::connect_server(struct sockaddr_in address, bool accumulate)
{
	if (connected)														// If the client is connected, return false
		return false;

	client_socket = socket(AF_INET, SOCK_STREAM, 0);					// Create client socket
	if (client_socket < 0)
	{
		perror("Client Socket Creation Failed");
		exit(EXIT_FAILURE);
	}

	struct timeval tv;													// Set timeout period for reception waiting
	tv.tv_sec = timeout_sec;											// Assume timeout = 5 seconds
	tv.tv_usec = timeout_u_sec;
	setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

	// Connect to the specified address
	int connection_status = connect(client_socket, (struct sockaddr*)& address, sizeof(address));
	if (connection_status < 0) {
		return false;
	}

	connected = true;

	if (!accumulate)													// If the data won't be accumulated then change it to zero 
	{																	// using mutex locks
		acc_mtx.lock();
		accumulation = 0;
		acc_mtx.unlock();

		av_mtx.lock();
		readings_number = 0;
		average = 0;
		av_mtx.unlock();
	}
	
	// Create two threads to handle reading data from the server and printing it
	std::thread read_thread(&TCPClient::read_server, this);
	read_thread.detach();
	std::thread print_thread (&TCPClient::handleprint, this);
	print_thread.detach();

	return true;

}

void TCPClient::read_server()
{
	double data;
	int bytes;

	// Thread executes while the client is connected
	while (connected)
	{
		// Wait for data to be received till timeout
		bytes = recv(client_socket, &data, sizeof(data), 0);
		if (bytes > 0)														// If data is received, update the stored values
		{
			update(data);
		}
		else
		{
			connected = false;												// If timeout occurs, close the connection
			close(client_socket);
		
		}
	}
}


TCPClient::~TCPClient()
{
	if (connected)

	{
		connected = false;													
		close(client_socket);
	}
}
