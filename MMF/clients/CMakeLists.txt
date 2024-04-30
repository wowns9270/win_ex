cmake_minimum_required(VERSION 3.10)
project(clients)

include_directories( ../include )

set(SOURCES
	clients.cpp
	)
	
add_executable(clients ${SOURCES})
