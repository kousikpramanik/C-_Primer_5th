add_executable(7.1 7.1/main.cpp 7.1/tnx_proc.cpp 7.1/tnx_proc.h)
target_link_libraries(7.1 PUBLIC Sales_data)
target_include_directories(7.1 PUBLIC 7.1)

add_library(Sales_data_2 STATIC 7.2/Sales_data_2.cpp 7.2/Sales_data_2.h)
target_include_directories(Sales_data_2 PUBLIC 7.2)

add_executable(7.3 7.3/main.cpp 7.3/tnx_proc_2.cpp)
target_link_libraries(7.3 PUBLIC Sales_data_2)
target_include_directories(7.3 PUBLIC 7.3)

add_library(Person INTERFACE)
target_include_directories(Person INTERFACE 7.4)

add_library(Person_2 INTERFACE)
target_include_directories(Person_2 INTERFACE 7.5)

add_library(Sales_data_3 STATIC 7.6/Sales_data_3.cpp 7.6/Sales_data_3.h)
target_include_directories(Sales_data_3 PUBLIC 7.6)

add_executable(7.7 7.7.cpp)
target_link_libraries(7.7 PUBLIC Sales_data_3)

add_library(Person_3 STATIC 7.9/Person_3.cpp 7.9/Person_3.h)
target_include_directories(Person_3 PUBLIC 7.9)

add_library(Sales_data_4 STATIC 7.11/Sales_data_4/Sales_data_4.cpp 7.11/Sales_data_4/Sales_data_4.h)
target_include_directories(Sales_data_4 PUBLIC 7.11/Sales_data_4)

add_executable(7.11 7.11/7.11.cpp)
target_link_libraries(7.11 PUBLIC Sales_data_4)

add_library(Sales_data_5 STATIC 7.12/Sales_data_5.cpp 7.12/Sales_data_5.h)
target_include_directories(Sales_data_5 PUBLIC 7.12)

add_executable(7.13 7.13.cpp)
target_link_libraries(7.13 PUBLIC Sales_data_5)

add_library(Sales_data_6 STATIC 7.14/Sales_data_6.cpp 7.14/Sales_data_6.h)
target_include_directories(Sales_data_6 PUBLIC 7.14)

add_library(Person_4 STATIC 7.15/Person_4.cpp 7.15/Person_4.h)
target_include_directories(Person_4 PUBLIC 7.15)

add_library(Sales_data_7 STATIC 7.21/Sales_data_7.cpp 7.21/Sales_data_7.h)
target_include_directories(Sales_data_7 PUBLIC 7.21)

add_library(Person_5 STATIC 7.22/Person_5.cpp 7.22/Person_5.h)
target_include_directories(Person_5 PUBLIC 7.22)

add_library(Screen INTERFACE)
target_include_directories(Screen INTERFACE 7.23)

add_library(Screen_2 INTERFACE)
target_include_directories(Screen_2 INTERFACE 7.24)

add_library(Sales_data_8 STATIC 7.26/Sales_data_8.cpp 7.26/Sales_data_8.h)
target_include_directories(Sales_data_8 PUBLIC 7.26)

add_library(Screen_3 INTERFACE)
target_include_directories(Screen_3 INTERFACE 7.27/Screen)

add_executable(7.27 7.27/7.27.cpp)
target_link_libraries(7.27 PUBLIC Screen_3)

add_library(Screen_4 INTERFACE)
target_include_directories(Screen_4 INTERFACE 7.29/Screen)

add_executable(7.29 7.29/7.29.cpp)
target_link_libraries(7.29 PUBLIC Screen_4)

add_library(X_Y INTERFACE)
target_include_directories(X_Y INTERFACE 7.30)

add_library(Window_mgr STATIC 7.32/Window_mgr.cpp 7.32/Window_mgr.h 7.32/Screen_5.h)
target_include_directories(Window_mgr PUBLIC 7.32)

add_library(Book INTERFACE)
target_include_directories(Book INTERFACE 7.40)

add_library(Sales_data_9 STATIC 7.41/Sales_data_9.cpp 7.41/Sales_data_9.h)
target_include_directories(Sales_data_9 PUBLIC 7.41)

add_library(Book_2 INTERFACE)
target_include_directories(Book_2 INTERFACE 7.42)

add_library(Person_6 STATIC 7.50/Person_6.cpp 7.50/Person_6.h)
target_include_directories(Person_6 PUBLIC 7.50)

add_library(Debug INTERFACE)
target_include_directories(Debug INTERFACE 7.53)

add_library(Account STATIC 7.57/Account.cpp 7.57/Account.h)
target_include_directories(Account PUBLIC 7.57)
