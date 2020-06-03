add_executable(16.2 16.2.cpp)

add_library(find INTERFACE)
target_include_directories(find INTERFACE 16.4/find)

add_executable(16.4 16.4/main.cpp)
target_link_libraries(16.4 PUBLIC find)

add_library(print INTERFACE)
target_include_directories(print INTERFACE 16.5)

add_library(begin_end INTERFACE)
target_include_directories(begin_end INTERFACE 16.6)

add_library(size INTERFACE)
target_include_directories(size INTERFACE 16.7)
