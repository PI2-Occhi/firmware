cmake_minimum_required(VERSION 3.10)

add_subdirectory(src)

project(mqtt)

# add the executable
add_executable(mqtt main.c)