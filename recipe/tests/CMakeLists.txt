cmake_minimum_required(VERSION 3.16)

project(vrs_consumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(vrslib CONFIG REQUIRED)

add_executable(vrs_consumer_test main.cpp)
target_link_libraries(vrs_consumer_test PRIVATE vrs::vrslib)
