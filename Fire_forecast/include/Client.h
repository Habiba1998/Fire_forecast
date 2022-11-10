#ifndef CLIENT_H
#define CLIENT_H

#include <mutex>
class Client
{
protected:
	
	static std::mutex print_mtx;			// Mutex to ensure atomic execution of std::cout on printing if clients run on different threads 
	bool connected;							// Indicates if the client is connected to a server
	double accumulation;					// The calculated accumulation
	double average;							// The calculated average
	unsigned int readings_number;			// Equals to the number of seconds as server sends data each second
	std::mutex acc_mtx;						// Mutex to ensure atomic update of the accumulation
	std::mutex av_mtx;						// Mutex to ensure atomic update of the average
	int print_duration;						// Duration in millisecond to print the data

public:
	Client(int d = 5000);					// Default duration = 5 seconds
	unsigned int get_readings_number()
	{
		return readings_number;
	}
	bool get_connected()
	{
		return connected;
	}
	
	double get_accumulation()
	{
		return accumulation;
	}
	double get_average()
	{
		return average;
	}
	void update(double reading);
	void handleprint();
	void print(double av, double acc);
	virtual ~Client() {}
};
#endif

