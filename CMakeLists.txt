cmake_minimum_required(VERSION 3.21)
project(TestMod)

set(Geode_DIR $ENV{GEODE_SDK})
find_package(Geode REQUIRED)

add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
