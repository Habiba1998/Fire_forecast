#include "Sensor.h"


Sensor::Sensor()
{
}

// Function to set the sensor value "for testing" using mutex locks
void Sensor::set_reading(double value)
{
	reading_mtx.lock();
	reading = value;
	reading_mtx.unlock();
}

// Function to get the sensor value
double Sensor::get_reading()
{
	double data;
	reading_mtx.lock();
	data = reading;
	reading_mtx.unlock();

	return data;
}

Sensor::~Sensor()
{
}
