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

add_library(StrBlob_2 STATIC 12.19/StrBlob.cpp 12.19/StrBlob.h)
target_include_directories(StrBlob_2 PUBLIC 12.19)

add_executable(12.20 12.20.cpp)
target_link_libraries(12.20 PUBLIC StrBlob_2)

add_library(StrBlob_3 STATIC 12.22/StrBlob.cpp 12.22/StrBlob.h)
target_include_directories(StrBlob_3 PUBLIC 12.22)

add_executable(12.23_literal 12.23/literal.cpp)
add_executable(12.23_string 12.23/string.cpp)
add_executable(12.24 12.24.cpp)
add_executable(12.26 12.26.cpp)

add_library(TextQuery STATIC 12.27/TextQuery.cpp 12.27/TextQuery.h)
target_include_directories(TextQuery PUBLIC 12.27)

add_executable(12.28 12.28.cpp)
add_executable(12.29 12.29.cpp)

add_library(TextQuery_2 STATIC 12.30/TextQuery/TextQuery.cpp 12.30/TextQuery/TextQuery.h)
target_include_directories(TextQuery_2 PUBLIC 12.30/TextQuery)

add_executable(12.30 12.30/main.cpp)
target_link_libraries(12.30 PUBLIC TextQuery_2)

add_library(TextQuery_3 STATIC 12.32/TextQuery.cpp 12.32/TextQuery.h)
target_link_libraries(TextQuery_3 PUBLIC StrBlob_3)
target_include_directories(TextQuery_3 PUBLIC 12.32)

add_library(TextQuery_4 STATIC 12.33/TextQuery.cpp 12.33/TextQuery.h)
target_include_directories(TextQuery_4 PUBLIC 12.33)
