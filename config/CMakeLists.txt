# this is CLion configuration file, ignore this file when using different IDE

cmake_minimum_required(VERSION 3.20)
project(Inventory_Manager)

set(CMAKE_CXX_STANDARD 20)

add_library(sqlite3
        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.c"
        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.h")


file(GLOB SOURCE_FILES ../source/*.cpp)
file(GLOB HEADER_FILES ../source/headers/*.h)
add_executable(Inventory_Manager ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(Inventory_Manager PUBLIC
        ../source/headers)

target_link_libraries(Inventory_Manager LINK_PUBLIC sqlite3)


#link_directories(
#        "C:/sqlite-x86"
#        "C:/sqlite"
#)
#add_library(sqlite3
#        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.c"
#        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.h")

