cmake_minimum_required(VERSION 3.21)
project(TestMod)

find_package(Geode REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    SOURCES src/main.cpp
)

# Esto es vital para que incluya tu botón en el archivo final
setup_geode_mod(${PROJECT_NAME} RESOURCES resources)
