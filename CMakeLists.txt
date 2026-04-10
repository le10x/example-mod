cmake_minimum_required(VERSION 3.25)

project(TestMod)

# Intenta buscarlo primero
find_package(Geode CONFIG)

if (NOT Geode_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Geode
        # ASEGÚRATE DE QUE LA URL ESTÉ COMPLETA ABAJO:
        GIT_REPOSITORY https://github.com
        GIT_TAG v5.5.3
    )
    FetchContent_MakeAvailable(Geode)
    find_package(Geode REQUIRED)
endif()

add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
