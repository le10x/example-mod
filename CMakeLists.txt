cmake_minimum_required(VERSION 3.25)

# Esto configura automáticamente las rutas del SDK en GitHub
include(FetchContent)
FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode
    GIT_TAG v5.5.3
)
FetchContent_MakeAvailable(Geode)

project(TestMod)

find_package(Geode REQUIRED)

# Agrega tu mod y sus archivos fuente
add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
