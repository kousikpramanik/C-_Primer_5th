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
