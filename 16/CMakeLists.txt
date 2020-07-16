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

add_library(Blob INTERFACE)
target_include_directories(Blob INTERFACE 16.12)

add_library(Screen_5 INTERFACE)
target_include_directories(Screen_5 INTERFACE 16.14)

add_library(Screen_6 INTERFACE)
target_include_directories(Screen_6 INTERFACE 16.15)

add_library(vector INTERFACE)
target_include_directories(vector INTERFACE 16.16)

add_library(16.19 INTERFACE)
target_include_directories(16.19 INTERFACE 16.19)

add_library(16.20 INTERFACE)
target_include_directories(16.20 INTERFACE 16.20)

add_library(DebugDelete INTERFACE)
target_include_directories(DebugDelete INTERFACE 16.21)

add_library(TextQuery_7 STATIC 16.22/TextQuery.cpp 16.22/TextQuery.h)
target_link_libraries(TextQuery_7 PRIVATE DebugDelete)
target_include_directories(TextQuery_7 PUBLIC 16.22)

add_executable(16.23 16.23.cpp)
target_link_libraries(16.23 PUBLIC TextQuery_7)
