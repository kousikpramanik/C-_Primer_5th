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
