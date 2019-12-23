add_library(9.4 STATIC 9.4/9.4.cpp 9.4/9.4.h)
target_include_directories(9.4 PUBLIC 9.4)

add_library(9.5 STATIC 9.5/9.5.cpp 9.5/9.5.h)
target_include_directories(9.5 PUBLIC 9.5)

add_executable(9.14 9.14.cpp)

add_executable(9.15 9.15.cpp)

add_executable(9.16 9.16.cpp)
