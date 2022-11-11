#ifndef SENSOR_NODE
#define SENSOR_NODE
#include "Sensor.h"

using namespace std;
class Sensor_node
{
private:
	Sensor* sensor;
protected:

	int duration;					// Duration in miliiseconds to update the clients
	bool active;					// The server becomes inactive on calling the destructor to stop the associated threads
	void send_reading();
	virtual void handle_send(double reading) = 0;

public:

	Sensor_node(Sensor* s, int d);
	virtual void run() = 0;
	virtual ~Sensor_node(){}
};
#endif
