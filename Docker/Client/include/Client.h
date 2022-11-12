#ifndef CLIENT_H
#define CLIENT_H

#include <mutex>
class Client
{
private:
	double accumulation;					// The calculated accumulation
	double average;							// The calculated average
	unsigned int readings_number;			// Equals to the number of seconds as server sends data each second
	bool connected;							// Indicates if the client is connected to a server
	std::mutex con_mtx;						// Mutex to ensure atomic update of connected
	std::mutex acc_mtx;						// Mutex to ensure atomic update of the accumulation
	std::mutex av_mtx;						// Mutex to ensure atomic update of the average

protected:
	
	static std::mutex print_mtx;			// Mutex to ensure atomic execution of std::cout on printing if clients run on different threads 

	int print_duration;						// Duration in millisecond to print the data

	void set_accumulation(double a);
	void set_average(double a);
	void set_readings_number(unsigned int a);
	void set_connected(bool v);
	void update(double reading);

public:
	Client(int d = 5000);					// Default duration = 5 seconds
	unsigned int get_readings_number();		
	bool get_connected();
	double get_accumulation();
	double get_average();
	
	
	void handleprint();
	void print(double av, double acc);
	virtual ~Client() {}
};
#endif

