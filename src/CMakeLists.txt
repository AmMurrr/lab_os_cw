cmake_minimum_required (VERSION 3.22)
project(lab_os_cp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp frblalloc.hpp frblalloc.cpp potalloc.hpp potalloc.cpp)
