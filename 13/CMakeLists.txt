add_executable(13.13 13.13.cpp)
add_executable(13.17_13.14 13.17/13.14.cpp)
add_executable(13.17_13.15 13.17/13.15.cpp)
add_executable(13.17_13.16 13.17/13.16.cpp)

add_library(Employee_2 STATIC 13.18/Employee.cpp 13.18/Employee.h)
target_include_directories(Employee_2 PUBLIC 13.18)

add_library(TextQuery_4 STATIC 13.21/TextQuery.cpp 13.21/TextQuery.h)
target_include_directories(TextQuery_4 PUBLIC 13.21)
