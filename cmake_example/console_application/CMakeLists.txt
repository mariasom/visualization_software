# nastavenie minimalnej verzie cmakeu + vypis verzie (momentalne najnovsi release je 3.23)
cmake_minimum_required(VERSION 3.12 FATAL_ERROR) 

message(STATUS "CMake version: ${CMAKE_VERSION}")

# nazov projektu, popis a definicia jazyka 
project(console_app
    DESCRIPTION "hello_world"
    LANGUAGES CXX
)

# automaticky prida zdrojaky a priecinky
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# nastavenie pouzivaneho jazykoveho standardu
set(CMAKE_CXX_STANDARD 17)

# vytvorenie *.exe suboru
add_executable(${PROJECT_NAME} src/hello_world.cpp)
add_executable(${PROJECT_NAME}_test src/hello_world_test.cpp)