#include "TCPServer.h"



int main()
{
	TCPServer s(8080, 5, 1000);
	s.set_reading(100);
	s.run();
	while (1)
	{
	}
	return 0;
}

