#include "Sensor_node.h"
#include "TCPServer.h"





int main()
{
	Sensor* x = new Sensor();
	x->set_reading(100);
	Sensor_node* s = new TCPServer (x, 8080, 5, 1000);					
	
	s->run();
	while (1)
	{
	}
	delete s;
	return 0;
}

