#ifndef SENSOR_H
#define SENSOR_H
#include <mutex>
class Sensor
{private:
	std::mutex reading_mtx;			// Mutex to ensure the atomic update of sensor reading 
	double reading;
public:
	Sensor();
	void set_reading(double value);
	double get_reading();
	~Sensor();
};
#endif

