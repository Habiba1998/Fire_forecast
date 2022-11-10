#include "gtest/gtest.h"
#include "TCPClient.h"
#include "Client.h"
#include "Sensor_node.h"
#include "TCPServer.h"
#include <thread>
#include <chrono>
#include <netinet/in.h>
#include <iostream>

TEST(OneClient1, ConnectionDoneSuccessfully)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c-> connect_server(address);
	std::this_thread::sleep_for(std::chrono::seconds(5));

	EXPECT_EQ(1, s->get_clients_number());
	EXPECT_TRUE(c->get_connected());

	delete s;
	delete c;
	system("pause");
}

TEST(OneClient2, DataReceivedSuccessfully)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	EXPECT_GE(100.0, c->get_accumulation());
	EXPECT_GE(100.0, c->get_average());
	
	delete s;
	delete c;
	system("pause");

}

TEST(OneClient3, AccumulationAndAverageUpdatedSuccessfully)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	s->set_reading(200);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	EXPECT_GE(300.0, c->get_accumulation());
	EXPECT_GE(150.0, c->get_average());

	delete s;
	delete c;
	system("pause");

}

TEST(OneClient4, ServerShutDownAndClientDisconnectAfterTimeOut)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	delete s;

	std::this_thread::sleep_for(std::chrono::seconds(7));				//Here timeout = 5

	EXPECT_FALSE(c->get_connected());

	delete c;
	system("pause");

}

TEST(OneClient5, ClientConnectToOtherServer)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	delete s;

	TCPServer s1(8000, 5, 1000);
	s1.set_reading(200);
	s1.run();

	std::this_thread::sleep_for(std::chrono::seconds(10));				//assume timeout = 5

	
	address.sin_port = htons(8000);
	flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	EXPECT_TRUE(c->get_connected());

	delete c;
	system("pause");

}

TEST(OneClient6, ServerRemoveTheClientFromTheListWhenItClosesTheSocket)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	delete c;

	std::this_thread::sleep_for(std::chrono::seconds(5));	

	EXPECT_EQ(0, s->get_clients_number());

	delete s;
	system("pause");

}

TEST(OneClient7, ClientConnectionFailOnConnectingToServerUsingWrongAddress)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	address.sin_port = htons(8081);
	TCPClient* c = new TCPClient();
	bool flag = c->connect_server(address);
	
	EXPECT_FALSE(flag);

	delete s;
	delete c;
	system("pause");

}


TEST(MoreThanOneClient1, TwoClientsConnectedSuccessfullyToServer)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c1 = new TCPClient();
	TCPClient* c2 = new TCPClient();
	bool flag1 = c1->connect_server(address);
	bool flag2 = c2->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(3));

	EXPECT_EQ(2, s->get_clients_number());
	EXPECT_TRUE(c1->get_connected());
	EXPECT_TRUE(c2->get_connected());

	delete s;
	delete c1;
	delete c2;
	system("pause");
}

TEST(MoreThanOneClient2, OneClientDisconnectButServerAndOtherClientsNotAffected)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c1 = new TCPClient();
	TCPClient* c2 = new TCPClient();
	bool flag1 = c1->connect_server(address);
	bool flag2= c2->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	delete c1;

	std::this_thread::sleep_for(std::chrono::seconds(20));

	EXPECT_EQ(1, s->get_clients_number());
	EXPECT_TRUE(c2->get_connected());
	
	delete s;
	delete c2;
	system("pause");
}

TEST(MoreThanOneClient3, AccumulationAndAverageUpdatedSuccessfully)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c1 = new TCPClient();
	bool flag1 = c1->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	TCPClient* c2 = new TCPClient();
	bool flag2 = c2->connect_server(address);
	s->set_reading(200);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	EXPECT_EQ(200.0, c2->get_accumulation());
	EXPECT_EQ(200.0, c2->get_average());

	delete s;
	delete c1;
	delete c2;
	system("pause");

}

TEST(MoreThanOneClient4, ServerShutDownAndClientsDisconnectAfterTimeOut)
{
	TCPServer* s = new TCPServer(8080, 5, 1000);
	struct sockaddr_in address = s->get_address();
	s->set_reading(100);
	s->run();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	TCPClient* c1 = new TCPClient();
	TCPClient* c2 = new TCPClient();
	bool flag1 = c1->connect_server(address);
	bool flag2 = c2->connect_server(address);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	delete s;

	std::this_thread::sleep_for(std::chrono::seconds(20));				//assume timeout = 5

	EXPECT_FALSE(c1->get_connected());
	EXPECT_FALSE(c2->get_connected());

	delete c1;
	delete c2;
	system("pause");

}



