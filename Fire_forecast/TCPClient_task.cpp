#include "Client.h"
#include "TCPClient.h"
#include <netinet/in.h>
#define port 8080


int main()
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	Client* c = new TCPClient (address);
	


	while (c->get_connected())					
	{
	}
	delete c;
	return 0;
}