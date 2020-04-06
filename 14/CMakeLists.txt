add_library(Sales_data_10 INTERFACE)
target_include_directories(Sales_data_10 INTERFACE 14.2)

add_library(String_5 STATIC 14.7/String.cpp 14.7/String.h)
target_include_directories(String_5 PUBLIC 14.7)
