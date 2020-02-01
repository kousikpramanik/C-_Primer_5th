add_executable(10.1 10.1.cpp)
add_executable(10.2 10.2.cpp)
add_executable(10.3 10.3.cpp)
add_executable(10.6 10.6.cpp)

add_library(elimDups STATIC 10.9/elimDups/elimDups.cpp 10.9/elimDups/elimDups.h)
target_include_directories(elimDups PUBLIC 10.9/elimDups)

add_executable(10.9 10.9/main.cpp)
target_link_libraries(10.9 PUBLIC elimDups)

add_executable(10.11 10.11.cpp)
target_link_libraries(10.11 PUBLIC elimDups)

add_executable(10.12 10.12.cpp)
target_link_libraries(10.12 PUBLIC Sales_data_8)

add_executable(10.13 10.13.cpp)

add_library(biggies STATIC 10.16/biggies.cpp 10.16/biggies.h)
target_link_libraries(biggies PRIVATE elimDups)
target_include_directories(biggies PUBLIC 10.16)

add_executable(10.17_10.12 10.17/10.12.cpp)
target_link_libraries(10.17_10.12 PUBLIC Sales_data_8)

add_library(biggies_2 STATIC 10.18/biggies.cpp 10.18/biggies.h)
target_link_libraries(biggies_2 PRIVATE elimDups)
target_include_directories(biggies_2 PUBLIC 10.18)

add_library(biggies_3 STATIC 10.19/biggies.cpp 10.19/biggies.h)
target_link_libraries(biggies_3 PRIVATE elimDups)
target_include_directories(biggies_3 PUBLIC 10.18)
