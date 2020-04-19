add_library(Sales_data_10 INTERFACE)
target_include_directories(Sales_data_10 INTERFACE 14.2)

add_library(String_5 STATIC 14.7/String.cpp 14.7/String.h)
target_include_directories(String_5 PUBLIC 14.7)

add_library(Book_3 INTERFACE)
target_include_directories(Book_3 INTERFACE 14.8)

add_library(Book_4 INTERFACE)
target_include_directories(Book_4 INTERFACE 14.12)

add_library(Sales_data_11 INTERFACE)
target_include_directories(Sales_data_11 INTERFACE 14.13)

add_library(Book_5 INTERFACE)
target_include_directories(Book_5 INTERFACE 14.15)

add_library(StrBlob_6 STATIC 14.16/StrBlob/StrBlob.cpp 14.16/StrBlob/StrBlob.h)
target_include_directories(StrBlob_6 PUBLIC 14.16/StrBlob)

add_library(StrVec_4 STATIC 14.16/StrVec/StrVec.cpp 14.16/StrVec/StrVec.h)
target_include_directories(StrVec_4 PUBLIC 14.16/StrVec)

add_library(String_6 STATIC 14.16/String/String.cpp 14.16/String/String.h)
target_include_directories(String_6 PUBLIC 14.16/String)

add_library(StrBlob_7 STATIC 14.18/StrBlob/StrBlob.cpp 14.18/StrBlob/StrBlob.h)
target_include_directories(StrBlob_7 PUBLIC 14.18/StrBlob)

add_library(StrVec_5 STATIC 14.18/StrVec/StrVec.cpp 14.18/StrVec/StrVec.h)
target_include_directories(StrVec_5 PUBLIC 14.18/StrVec)

add_library(String_7 STATIC 14.18/String/String.cpp 14.18/String/String.h)
target_include_directories(String_7 PUBLIC 14.18/String)

add_library(Book_6 STATIC 14.19/Book.cpp 14.19/Book.h)
target_include_directories(Book_6 PUBLIC 14.19)

add_library(Sales_data_12 INTERFACE)
target_include_directories(Sales_data_12 INTERFACE 14.21/Sales_data)

add_library(Sales_data_13 INTERFACE)
target_include_directories(Sales_data_13 INTERFACE 14.22)

add_library(StrVec_6 STATIC 14.23/StrVec.cpp 14.23/StrVec.h)
target_include_directories(StrVec_6 PUBLIC 14.23)

add_library(Book_7 STATIC 14.24/Book.cpp 14.24/Book.h)
target_include_directories(Book_7 PUBLIC 14.24)

add_library(StrVec_7 STATIC 14.25/StrVec/StrVec.cpp 14.25/StrVec/StrVec.h)
target_include_directories(StrVec_7 PUBLIC 14.25/StrVec)

add_library(String_8 STATIC 14.25/String/String.cpp 14.25/String/String.h)
target_include_directories(String_8 PUBLIC 14.25/String)

add_library(StrBlob_8 STATIC 14.25/StrBlob/StrBlob.cpp 14.25/StrBlob/StrBlob.h)
target_include_directories(StrBlob_8 PUBLIC 14.25/StrBlob)

add_library(StrBlob_9 STATIC 14.27/StrBlob.cpp 14.27/StrBlob.h)
target_include_directories(StrBlob_9 PUBLIC 14.27)

add_library(StrBlob_10 INTERFACE)
target_include_directories(StrBlob_10 INTERFACE 14.28)

add_library(StrBlob_11 INTERFACE)
target_include_directories(StrBlob_11 INTERFACE 14.30)

add_executable(14.32 14.32.cpp)
target_link_libraries(14.32 PUBLIC StrBlob_11)

add_library(if_then_else INTERFACE)
target_include_directories(if_then_else INTERFACE 14.34)

add_library(line_istream INTERFACE)
target_include_directories(line_istream INTERFACE 14.35)

add_executable(14.36 14.36.cpp)
target_link_libraries(14.36 PUBLIC line_istream)

add_executable(14.37 14.37.cpp)
add_executable(14.38 14.38.cpp)
add_executable(14.39 14.39.cpp)

add_library(biggies_7 STATIC 14.40/biggies.cpp 14.40/biggies.h)
target_link_libraries(biggies_7 PRIVATE elimDups)
target_include_directories(biggies_7 PUBLIC 14.40)
