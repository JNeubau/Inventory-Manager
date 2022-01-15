# this is CLion configuration file, ignore this file when using different IDE

cmake_minimum_required(VERSION 3.20)
project(Inventory_Manager)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES ../source/*.cpp)
add_executable(Inventory_Manager ${SOURCE_FILES})
target_link_libraries(Inventory_Manager LINK_PUBLIC sqlite3)