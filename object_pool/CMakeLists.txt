project(objpool)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)

# Enable the testing features.
enable_testing()
# To use the googletest
find_package(GTest REQUIRED)
# Enable the GoogleTest integration.
include(GoogleTest)

# Main executable
add_subdirectory(src)

# Test using googletest
add_subdirectory(test)