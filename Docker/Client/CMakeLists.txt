cmake_minimum_required (VERSION 2.8.11)
project (Fire_forecast)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

# Executables for sample client and server instances interaction
add_executable(client_task TCPClient_task.cpp)

target_sources(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_sources(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/TCPClient.cpp)
target_include_directories(client_task PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)







