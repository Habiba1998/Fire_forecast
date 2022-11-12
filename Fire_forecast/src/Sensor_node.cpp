#include "Sensor_node.h"
#include <chrono>
#include <thread>






Sensor_node::Sensor_node(Sensor* s, int d)
{
	clients_number = 0;
	sensor = s;
	duration = d;
}

// Function to get the current number of connected clients using mutex locks
unsigned int Sensor_node::get_clients_number()
{
	unsigned int v;
	clients_mtx.lock();
	v = clients_number;
	clients_mtx.unlock();
	return v;
}

// Function to ensure that the sensor reading is sent periodically
void Sensor_node::send_reading(void* new_socket)
{
	double current_reading;
	auto ms = std::chrono::steady_clock::now();
	bool status;
	while (active)
	{
		ms = std::chrono::steady_clock::now() + std::chrono::milliseconds(duration);
		current_reading = sensor->get_reading();
		status = handle_send(current_reading, new_socket);
		if (!status)
		{
			break;												// If send fail, exit the loop to terminate the thread operation
		}
		std::this_thread::sleep_until(ms);						// To ensure periodic update of the clients
	}
}

void Sensor_node::add_client()
{
	clients_mtx.lock();
	clients_number ++;
	clients_mtx.unlock();
}

void Sensor_node::remove_client()
{
	clients_mtx.lock();
	clients_number --;
	clients_mtx.unlock();
}


