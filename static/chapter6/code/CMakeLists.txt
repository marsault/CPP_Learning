cmake_minimum_required(VERSION 3.16)
project(Inheritance)

add_executable(hierarchy
    1-hierarchy/Hierarchy.cpp
    1-hierarchy/Boss.cpp
    1-hierarchy/Boss.h
    1-hierarchy/Staff.cpp
    1-hierarchy/Staff.h
    1-hierarchy/Intern.cpp
    1-hierarchy/Intern.h
    1-hierarchy/Rank.h
)
target_compile_features(hierarchy PRIVATE cxx_std_17)

add_executable(farm
    2-farm/FarmHouse.cpp
    2-farm/Animal.h
    2-farm/Cat.h
    2-farm/Chicken.h
    2-farm/Cow.h
    2-farm/Dog.h
)
target_compile_features(farm PRIVATE cxx_std_17)

add_executable(vehicles
    3-vehicles/Program.cpp
    3-vehicles/Car.h
    3-vehicles/Scooter.h
    3-vehicles/Vehicle.h
)
target_compile_features(vehicles PRIVATE cxx_std_17)
