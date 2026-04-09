cmake_minimum_required(VERSION 3.21)
project(TestMod)

find_package(Geode REQUIRED)

# Si tu carpeta se llama "src", aquí DEBE decir "src"
add_geode_mod(${PROJECT_NAME} SOURCES src/main.cpp)
