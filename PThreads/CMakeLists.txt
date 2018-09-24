cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(PThreads VERSION 0.1.0)

file(GLOB SRCS
    "src/*.cpp"
)

include_directories("./include")
add_executable(PThreads src/main.cpp ${SRCS})

TARGET_LINK_LIBRARIES( PThreads
pthread
)