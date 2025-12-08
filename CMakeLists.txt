cmake_minimum_required(VERSION 3.16)

set(NAME omdi-demo)

project(${NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(oh-my-dear-imgui CONFIG REQUIRED)

set(SRC main.cpp)
add_executable(${NAME} ${SRC})

target_link_libraries(${NAME} PRIVATE oh-my-dear-imgui::oh-my-dear-imgui)
