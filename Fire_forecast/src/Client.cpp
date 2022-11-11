#include "Client.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

// Initialize static variables
std::mutex Client::print_mtx;




Client::Client(int d)
{
	print_duration = d;
	readings_number = 0;
	accumulation = 0;
	average = 0;
	
}
// Setters
void Client::set_accumulation(double a)
{
	acc_mtx.lock();
	accumulation = a;
	acc_mtx.unlock();
}

void Client::set_average(double a)
{
	av_mtx.lock();
	average = a;
	av_mtx.unlock();
}

void Client::set_readings_number(unsigned int a)
{
	acc_mtx.lock();
	readings_number = a;
	acc_mtx.unlock();
}
void Client::set_connected(bool v)
{
	con_mtx.lock();
	connected = v;
	con_mtx.unlock();
}

// Getters
bool Client::get_connected()
{
	bool r;
	con_mtx.lock();
	r = connected;
	con_mtx.unlock();
	return r;
}
unsigned int Client::get_readings_number()
{
	unsigned int v;
	av_mtx.lock();
	v = readings_number;
	av_mtx.unlock();

	return v;
}

double Client::get_accumulation()
{
	double v;
	acc_mtx.lock();
	v = accumulation;
	acc_mtx.unlock();
	return v;
}

double Client::get_average()	
{
	double v;
	av_mtx.lock();
	v = average;
	av_mtx.unlock();
	return v;
}

// Function to update data based on the reading
void Client::update(double reading)
{
	acc_mtx.lock();
	accumulation += reading;
	acc_mtx.unlock();

	av_mtx.lock();
	readings_number++;
	average = accumulation / readings_number;
	av_mtx.unlock();
}

// Function to print the computed data each print_duration period
void Client::handleprint()
{
	auto ms = std::chrono::steady_clock::now();
	double current_average, current_accumulation; 
	bool first_iteration = true;				// To make the first print after print_duratio since the client has just been connected


	// The loop executes while the client is connected to a server
	while (get_connected())
	{
		ms = std::chrono::steady_clock::now() + std::chrono::milliseconds(print_duration);
		if (!first_iteration)
		{
			// Access variables using mutex locks
			
			current_average = get_average();
			current_accumulation = get_accumulation();
			

			// Print the data
			print_mtx.lock();
			print(current_average, current_accumulation);
			print_mtx.unlock();

		}
		else
		{
			first_iteration = false;
		}

		std::this_thread::sleep_until(ms);		// To ensure periodic execution
	}
}


// Function to print the average and accumulation
void Client::print(double av, double acc)
{
	cout << "Average over time equals " << av << endl;
	cout << "Accumulation over time equals " << acc << endl;
	cout << endl;
}


