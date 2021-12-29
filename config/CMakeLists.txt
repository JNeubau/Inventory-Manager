# this is CLion configuration file, ignore this file when using different IDE

cmake_minimum_required(VERSION 3.20)
project(Inventory_Manager)

set(CMAKE_CXX_STANDARD 20)

#link_directories(
#        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3"
#)
add_library(sqlite3
        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.c"
        "C:/Users/neuba/CodeProjects/PO-proj/Inventory-Manager/Inventory-Manager/sqlite3/sqlite3.h")

add_executable(Inventory_Manager
        ../main.cpp ../headers/asprintf.h ../headers/product.h)
target_link_libraries(Inventory_Manager LINK_PUBLIC sqlite3)
