cmake_minimum_required(VERSION 4.1)
project(DoomClone)

set(CMAKE_CXX_STANDARD 20)
file(GLOB PROJECT_SOURCES
        "main.cpp"
        "src/*.cpp"
        "test/*.cpp"
)
include_directories(include)
include_directories(test)
add_executable(DoomClone ${PROJECT_SOURCES})
