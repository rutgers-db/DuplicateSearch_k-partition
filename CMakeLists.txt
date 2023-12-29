cmake_minimum_required(VERSION 3.10)


# Set the project name and version
project(QueryCreation VERSION 1.0)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

# Add the executable
add_executable(build ./src/build.cpp)
add_executable(main ./src/main.cpp)

find_package(OpenMP REQUIRED)
target_link_libraries(build PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)


# Include directories
target_include_directories(build PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")