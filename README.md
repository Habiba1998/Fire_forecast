# Fire_forecast

## Build and Run Using CMake

1. Install CMake in Unix/Linux.<br />
2. Clone the repository.<br />
3. Navigate to the project folder then run the following commands:<br />
&nbsp;&nbsp; i. cmake -S . -B build<br />
&nbsp;&nbsp; ii. cmake --build build<br />
4. To execute the tests, run the following command from the project folder:<br />
&nbsp;&nbsp; i. cd build && ctest<br />
5. To execute the sample client and server, run the following command from the project folder:<br />
&nbsp;&nbsp; i. cd build<br />
&nbsp;&nbsp; ii. cd Fire_forecast<br />
&nbsp;&nbsp; iii. ./server_task  "To run the server task", ./client_task "To run the client task".<br />

## Build and Run Using Docker

1. Install Docker.<br />
2. Clone the repository.<br />
3. Navigate to Docker/Server then run: docker build -t server<br />
4. Navigate to Docker/Client then run: docker build -t client<br />
5. Run both images using:<br />
&nbsp;&nbsp;i. docker run --network=host --name ipc_server_dns_name server<br />
&nbsp;&nbsp;ii. docker run --network=host client<br />

Alternatively, you can pull the two images and run them directly from the following links:<br />
https://hub.docker.com/repository/docker/2724180806/server<br />
https://hub.docker.com/repository/docker/2724180806/client<br />
              
