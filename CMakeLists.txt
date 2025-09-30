cmake_minimum_required(VERSION 3.10.0)

project(ipv4calc VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

add_subdirectory(src)
