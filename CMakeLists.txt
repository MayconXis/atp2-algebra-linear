cmake_minimum_required(VERSION 4.1)
project(Atp2_Algebra C)

set(CMAKE_C_STANDARD 99)

add_executable(Atp2_Algebra src/main.c
        src/matrix.c
        include/matrix.h)
