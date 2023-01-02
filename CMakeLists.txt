cmake_minimum_required(VERSION 3.23)
project(Trabalho_Algoritmos_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Trabalho_Algoritmos_2
        FlightGraph.cpp
        FlightGraph.h
        Manager.cpp
        Manager.h
        Airport.cpp
        Airport.h
        Airlines.cpp
        Airlines.h
        Menus.cpp
        Manager.h
        main.cpp)
