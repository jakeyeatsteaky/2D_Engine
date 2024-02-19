cmake_minimum_required(VERSION 3.10)

# Set your project name
project(2D_Engine)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(/W4 /WX)

# Find the SDL2 package
find_package(SDL2 REQUIRED)
set(SDL2_INCLUDE_DIRS "C:\\SDL2\\include")

# Include the SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS}, ./src)

# File GLOB to collect all source files from /src directory
file(GLOB PROJECT_SOURCES "src/*.cpp")

# Define the source files for your project
add_executable(2D_Engine main.cpp ${PROJECT_SOURCES})

# Link SDL2 to your project
target_link_libraries(2D_Engine ${SDL2_LIBRARIES})
