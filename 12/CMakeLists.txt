add_library(StrBlob STATIC 12.2/StrBlob.cpp 12.2/StrBlob.h)
target_include_directories(StrBlob PUBLIC 12.2)

add_executable(12.6 12.6.cpp)
add_executable(12.7 12.7.cpp)
