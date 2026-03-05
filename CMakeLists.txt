cmake_minimum_required(VERSION 3.10)
project(AlgoEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Find threading library (Crucial for cross-platform compiling)
find_package(Threads REQUIRED)

add_executable(engine 
    src/main.cpp 
    src/AlgoEngine.cpp 
    src/StringMatcher.cpp
    src/ParallelEngine.cpp
)

# Link the threading library
target_link_libraries(engine Threads::Threads)