cmake_minimum_required(VERSION 3.14)
project(sudokuuu C)

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-fmessage-length=0 -ansi -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )



add_executable(sudokuuu
        Game.c
        Game.h
        main.c
        MainAux.c
        MainAux.h
        Parser.c
        Parser.h
        Solver.c
        Solver.h
        SPBufferset.h)
