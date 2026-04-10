cmake_minimum_required(VERSION 3.25)

project(TestMod)

# Esto busca el SDK de Geode. Si falla, intenta descargarlo automáticamente.
find_package(Geode CONFIG)

if (NOT Geode_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Geode
        GIT_REPOSITORY https://github.com
        GIT_TAG v5.5.3
    )
    FetchContent_MakeAvailable(Geode)
    find_package(Geode REQUIRED)
endif()

# Asegúrate de que tu código esté en la carpeta src/ y se llame main.cpp
add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
