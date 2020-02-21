add_executable(11.3 11.3.cpp)
add_executable(11.4 11.4.cpp)
add_executable(11.7 11.7.cpp)
add_executable(11.8 11.8.cpp)
add_executable(11.12 11.12.cpp)

add_executable(11.14 11.14.cpp)
target_link_libraries(11.14 PUBLIC Date_2)

add_executable(11.20 11.20.cpp)
add_executable(11.23 11.23.cpp)
add_executable(11.31 11.31.cpp)

add_library(word_transform STATIC 11.33/word_transform/word_transform.cpp 11.33/word_transform/word_transform.h)
target_include_directories(word_transform PUBLIC 11.33/word_transform)

add_executable(11.33 11.33/main.cpp)
target_link_libraries(11.33 PUBLIC word_transform)

add_executable(11.38_11.3 11.38/11.3.cpp)

add_library(11.38_word_transform STATIC
        11.38/11.33/word_transform/word_transform.cpp
        11.38/11.33/word_transform/word_transform.h)
target_include_directories(11.38_word_transform PUBLIC 11.38/11.33/word_transform)

add_executable(11.38_11.33 11.38/11.33/main.cpp)
target_link_libraries(11.38_11.33 PUBLIC 11.38_word_transform)
