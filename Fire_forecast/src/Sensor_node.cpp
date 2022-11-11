#include "Sensor_node.h"
#include <chrono>
#include <thread>


//##########commit



Sensor_node::Sensor_node(Sensor* s, int d)
{
	sensor = s;
	duration = d;
}


void Sensor_node::send_reading()
{
	double current_reading;
	auto ms = std::chrono::steady_clock::now();
	while (active)
	{
		ms = std::chrono::steady_clock::now() + std::chrono::milliseconds(duration);
		current_reading = sensor->get_reading();
		handle_send(current_reading);
		std::this_thread::sleep_until(ms);						// To ensure periodic update of the clients
	}
}


