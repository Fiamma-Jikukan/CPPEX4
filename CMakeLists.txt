cmake_minimum_required(VERSION 3.30)
project(CPPEX4)

set(CMAKE_CXX_STANDARD 11)

add_executable(CPPEX4 main.cpp
        Cell.cpp
        Cell.h
        Forest.cpp
        Forest.h
        Drone.cpp
        Drone.h
        Search.cpp
        Search.h
        TDVector.cpp
        TDVector.h
        BinarySearchTree.cpp
        BinarySearchTree.h
        SingleRotorDrone.cpp
        SingleRotorDrone.h
        MultiRotorDrone.cpp
        MultiRotorDrone.h
        FixedWingDrone.cpp
        FixedWingDrone.h
        FixedWingHybridVTOL.cpp
        FixedWingHybridVTOL.h)
