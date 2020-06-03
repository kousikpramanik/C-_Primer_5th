cmake_minimum_required(VERSION 3.15)
project("C++ Primer 5th"
        VERSION 0.15
        DESCRIPTION "Solutions to exercises of C++ Primer by Lippman et al., 5th edition"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -pedantic -march=native)

add_subdirectory(book-resources)

add_subdirectory(1)
add_subdirectory(2)
add_subdirectory(3)
add_subdirectory(4)
add_subdirectory(5)
add_subdirectory(6)
add_subdirectory(7)
add_subdirectory(8)
add_subdirectory(9)
add_subdirectory(10)
add_subdirectory(11)
add_subdirectory(12)
add_subdirectory(13)
add_subdirectory(14)
add_subdirectory(15)
add_subdirectory(16)
