cmake_minimum_required(VERSION 3.10)
project(class_system)
 
include_directories(include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(class_system ${SOURCES})