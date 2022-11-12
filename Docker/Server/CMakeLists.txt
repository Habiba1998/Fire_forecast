cmake_minimum_required (VERSION 2.8.11)
project (Fire_forecast)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

# Executables for sample client and server instances interaction
add_executable (server_task TCPServer_task.cpp)


target_sources(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor_node.cpp)
target_sources(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPServer.cpp)
target_sources(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor.cpp)
target_include_directories(server_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)









