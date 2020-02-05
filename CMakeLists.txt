cmake_minimum_required(VERSION 3.15)
project("C++ Primer 5th"
        VERSION 0.9
        DESCRIPTION "Solutions to exercises of C++ Primer by Lippman et al., 5th edition"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

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
