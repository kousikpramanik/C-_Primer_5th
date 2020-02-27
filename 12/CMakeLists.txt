add_library(StrBlob STATIC 12.2/StrBlob.cpp 12.2/StrBlob.h)
target_include_directories(StrBlob PUBLIC 12.2)

add_executable(12.6 12.6.cpp)
add_executable(12.7 12.7.cpp)

add_library(connect STATIC
        12.14/connect/connect.h
        12.14/connect/private/connect.c
        12.14/connect/private/connect_private.h)
target_include_directories(connect PRIVATE 12.14/connect/private)
target_include_directories(connect PUBLIC 12.14/connect)

add_executable(12.14 12.14/main.cpp)
target_link_libraries(12.14 PUBLIC connect)

add_executable(12.15 12.15.cpp)
target_link_libraries(12.15 PUBLIC connect)
