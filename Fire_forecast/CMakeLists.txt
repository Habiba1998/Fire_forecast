cmake_minimum_required (VERSION 2.8.11)
project (Fire_forecast)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

#server and client libraries for testing
add_library (server)
add_library (client) 

# Executables for sample client and server instances interaction
add_executable (server_task TCPServer_task.cpp)
add_executable(client_task TCPClient_task.cpp)

target_sources(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor_node.cpp)
target_sources(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPServer.cpp)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_sources(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPClient.cpp)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_sources(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor_node.cpp)
target_sources(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPServer.cpp)
target_include_directories(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_sources(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPClient.cpp)
target_include_directories(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)








