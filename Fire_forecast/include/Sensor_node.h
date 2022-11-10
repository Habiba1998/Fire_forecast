#ifndef SENSOR_NODE
#define SENSOR_NODE

#include <mutex>

using namespace std;
class Sensor_node
{
protected:
	static std::mutex reading_mtx;	// Mutex to ensure the atomic update of sensor reading
	double reading;
	int duration;					// Duration in miliiseconds to update the clients
	bool active;					// The server becomes inactive on calling the destructor to stop the associated threads

public:
	Sensor_node(int d);

	void set_reading(double value);

	double get_reading()
	{
		return reading;
	}

	virtual void run() = 0;			
	virtual void handle_send(double reading) = 0;
	void send_reading();
	virtual ~Sensor_node(){}
};
#endif
