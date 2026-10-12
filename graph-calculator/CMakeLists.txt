cmake_minimum_required(VERSION 3.21)

project(GraphCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(calculator
    main.cpp
    calculator.cpp
)
target_link_libraries(calculator PRIVATE Qt6::Widgets)
