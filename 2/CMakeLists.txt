add_executable(2.4 2.4.cpp)
add_executable(2.8 2.8.cpp)
add_executable(2.18 2.18.cpp)
add_executable(2.34 2.34.cpp)
add_executable(2.35 2.35.cpp)
add_executable(2.41_1.20 2.41/1.20.cpp)
add_executable(2.41_1.21 2.41/1.21.cpp)
add_executable(2.41_1.22 2.41/1.22.cpp)
add_executable(2.41_1.23 2.41/1.23.cpp)
add_executable(2.41_1.25 2.41/1.25.cpp)

add_library(Sales_data INTERFACE)
target_include_directories(Sales_data INTERFACE 2.42/Sales_data)

add_executable(2.42_1.20 2.42/1.20.cpp)
target_link_libraries(2.42_1.20 PUBLIC Sales_data)

add_executable(2.42_1.21 2.42/1.21.cpp)
target_link_libraries(2.42_1.21 PUBLIC Sales_data)

add_executable(2.42_1.22 2.42/1.22.cpp)
target_link_libraries(2.42_1.22 PUBLIC Sales_data)

add_executable(2.42_1.23 2.42/1.23.cpp)
target_link_libraries(2.42_1.23 PUBLIC Sales_data)

add_executable(2.42_1.25 2.42/1.25.cpp)
target_link_libraries(2.42_1.25 PUBLIC Sales_data)
