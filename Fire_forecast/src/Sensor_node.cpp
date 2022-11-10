#include "Sensor_node.h"
#include <chrono>
#include <thread>


// Initialize the static member
std::mutex Sensor_node::reading_mtx;




Sensor_node::Sensor_node(int d)
{
	duration = d;
}

void Sensor_node::set_reading(double value)
{
	reading_mtx.lock();
	reading = value;
	reading_mtx.unlock();
}

void Sensor_node::send_reading()
{
	double current_reading;
	auto ms = std::chrono::steady_clock::now();
	while (active)
	{
		ms = std::chrono::steady_clock::now() + std::chrono::milliseconds(duration);
		reading_mtx.lock();
		current_reading = reading;
		reading_mtx.unlock();
		handle_send(current_reading);
		std::this_thread::sleep_until(ms);						// To ensure periodic update of the clients
	}
}


