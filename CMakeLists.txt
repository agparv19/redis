cmake_minimum_required(VERSION 3.10)
project(redis)

# Add executable
add_executable(redis server.cpp
                     type.cpp
                     RESPParser.cpp
                     redisstore.cpp
                     common.cpp
                     cmds.cpp
                     config.cpp)

# for debug info                     
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
