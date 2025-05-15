cmake_minimum_required(VERSION 3.20)
project(stratego)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library target as interface until we add source files
add_library(stratego-lib INTERFACE)

# Create executable target
add_executable(stratego main.cpp)

# Link the library with the executable
target_link_libraries(stratego PRIVATE stratego-lib)

# Include directories
target_include_directories(stratego-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stratego-lib)
target_include_directories(stratego PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/stratego-lib)
