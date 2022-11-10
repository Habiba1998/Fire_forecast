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
	while (connected)
	{
		ms = std::chrono::steady_clock::now() + std::chrono::milliseconds(print_duration);
		if (!first_iteration)
		{
			// Access variables using mutex locks
			av_mtx.lock();
			current_average = average;
			av_mtx.unlock();
			acc_mtx.lock();
			current_accumulation = accumulation;
			acc_mtx.unlock();

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


