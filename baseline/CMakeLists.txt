cmake_minimum_required(VERSION 3.10)


# Set the project name and version
project(QueryCreation VERSION 1.0)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Add the executable
add_executable(runBF ./src/runBF.cpp)
add_executable(runSD ./src/runSD.cpp)
add_executable(runKMIN ./src/runKMIN.cpp)
add_executable(runOPH ./src/runOPH.cpp)
add_executable(runFaeire ./src/runFaerie.cpp)

find_package(OpenMP REQUIRED)
target_link_libraries(runBF PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(runSD PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(runKMIN PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(runOPH PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(runFaeire PUBLIC OpenMP::OpenMP_CXX)

# Include directories
target_include_directories(runBF PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")
target_include_directories(runSD PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")
target_include_directories(runKMIN PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")
target_include_directories(runOPH PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")
target_include_directories(runFaeire PUBLIC "${PROJECT_BINARY_DIR}" "./src/util")