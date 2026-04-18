cmake_minimum_required(VERSION 4.1)
project(DoomClone)

set(CMAKE_CXX_STANDARD 20)
file(GLOB PROJECT_SOURCES
        "main.cpp"
        "src/*.cpp"
)
include_directories(include)
add_executable(DoomClone ${PROJECT_SOURCES})
