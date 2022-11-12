#ifndef SENSOR_NODE
#define SENSOR_NODE
#include "Sensor.h"

using namespace std;
class Sensor_node
{
private:
	Sensor* sensor;
	std::mutex clients_mtx;			// Mutex to ensure atomic update of clients_number
	unsigned int clients_number;	// Keep Track of number of connected clients;

protected:

	int duration;					// Duration in miliiseconds to update the clients
	bool active;					// The server becomes inactive on calling the destructor to stop the associated threads
	void send_reading(void* new_socket = nullptr);
	void add_client();
	void remove_client();
	virtual bool handle_send(double reading, void* new_socket = nullptr) = 0;// void* to support different communication methods in the future

public:

	Sensor_node(Sensor* s, int d);
	unsigned int get_clients_number();
	virtual void run() = 0;
	virtual ~Sensor_node(){}
};
#endif
