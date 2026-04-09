cmake_minimum_required(VERSION 3.21)
project(TestMod)

find_package(Geode REQUIRED PATHS $ENV{GEODE_SDK})

add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
