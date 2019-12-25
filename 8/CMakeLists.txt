add_library(8.1 STATIC 8.1/8.1.cpp 8.1/8.1.h)
target_include_directories(8.1 PUBLIC 8.1)

add_executable(8.2 8.2.cpp)
target_link_libraries(8.2 PUBLIC 8.1)

add_library(8.4 STATIC 8.4/8.4.cpp 8.4/8.4.h)
target_include_directories(8.4 PUBLIC 8.4)

add_library(8.5 STATIC 8.5/8.5.cpp 8.5/8.5.h)
target_include_directories(8.5 PUBLIC 8.5)

add_executable(8.6 8.6.cpp)
target_link_libraries(8.6 PUBLIC Sales_data_8)

add_executable(8.7 8.7.cpp)
target_link_libraries(8.7 PUBLIC Sales_data_8)

add_executable(8.9 8.9.cpp)
target_link_libraries(8.9 PUBLIC 8.1)

add_library(8.10 STATIC 8.10/8.10.cpp 8.10/8.10.h)
target_link_libraries(8.10 PRIVATE 8.4)
target_include_directories(8.10 PUBLIC 8.10)

add_executable(8.11 8.11.cpp)
add_executable(8.13 8.13.cpp)
