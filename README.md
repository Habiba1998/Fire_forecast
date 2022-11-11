# Fire_forecast

## Execution Steps

1. Install CMake in Unix/Linux.<br />
2. Clone the repository.<br />
3. To build the project and the tests, navigate to the project folder then run the following commands:<br />
&nbsp;&nbsp; i. cmake -S . -B build<br />
&nbsp;&nbsp; ii. cmake --build build<br />
4. To execute the tests, run the following command from the project folder:<br />
&nbsp;&nbsp; i. cd build && ctest<br />
5. To execute the sample client and server, run the following command from the project folder:<br />
&nbsp;&nbsp; i. cd build<br />
&nbsp;&nbsp; ii. cd Fire_forecast<br />
&nbsp;&nbsp; iii. ./server_task  "To run the servertask", ./client_task "To run the clienttask".<br />
              
