add_executable(13.13 13.13.cpp)
add_executable(13.17_13.14 13.17/13.14.cpp)
add_executable(13.17_13.15 13.17/13.15.cpp)
add_executable(13.17_13.16 13.17/13.16.cpp)

add_library(Employee_2 STATIC 13.18/Employee.cpp 13.18/Employee.h)
target_include_directories(Employee_2 PUBLIC 13.18)

add_library(TextQuery_4 STATIC 13.21/TextQuery.cpp 13.21/TextQuery.h)
target_include_directories(TextQuery_4 PUBLIC 13.21)

add_library(HasPtr INTERFACE)
target_include_directories(HasPtr INTERFACE 13.22)

add_library(StrBlob_4 STATIC 13.26/StrBlob.cpp 13.26/StrBlob.h)
target_include_directories(StrBlob_4 PUBLIC 13.26)

add_library(HasPtr_2 INTERFACE)
target_include_directories(HasPtr_2 INTERFACE 13.27)

add_library(BinStrTree INTERFACE)
target_include_directories(BinStrTree INTERFACE 13.28)

add_library(HasPtr_3 STATIC 13.30/HasPtr.cpp 13.30/HasPtr.h)
target_include_directories(HasPtr_3 PUBLIC 13.30)

add_library(HasPtr_4 STATIC 13.31/HasPtr/HasPtr.cpp 13.31/HasPtr/HasPtr.h)
target_include_directories(HasPtr_4 PUBLIC 13.31/HasPtr)

add_executable(13.31 13.31/main.cpp)
target_link_libraries(13.31 PUBLIC HasPtr_4)

add_library(Message_Folder STATIC 13.36/Message_Folder.cpp 13.36/Message_Folder.h)
target_include_directories(Message_Folder PUBLIC 13.36)

add_library(StrVec STATIC 13.40/StrVec.cpp 13.40/StrVec.h)
target_include_directories(StrVec PUBLIC 13.40)

add_library(TextQuery_5 STATIC 13.42/TextQuery.cpp 13.42/TextQuery.h)
target_link_libraries(TextQuery_5 PUBLIC StrVec)
target_include_directories(TextQuery_5 PUBLIC 13.42)

add_library(StrVec_2 STATIC 13.43/StrVec.cpp 13.43/StrVec.h)
target_include_directories(StrVec_2 PUBLIC 13.43)

add_library(String STATIC 13.44/String.cpp 13.44/String.h)
target_include_directories(String PUBLIC 13.44)

add_library(String_2 STATIC 13.47/String.cpp 13.47/String.h)
target_include_directories(String_2 PUBLIC 13.47)

add_executable(13.48 13.48.cpp)
target_link_libraries(13.48 PUBLIC String_2)

add_library(Message_Folder_2 STATIC 13.49/Message_Folder/Message_Folder.cpp 13.49/Message_Folder/Message_Folder.h)
target_include_directories(Message_Folder_2 PUBLIC 13.49/Message_Folder)

add_library(StrVec_3 STATIC 13.49/StrVec/StrVec.cpp 13.49/StrVec/StrVec.h)
target_include_directories(StrVec_3 PUBLIC 13.49/StrVec)

add_library(String_3 STATIC 13.49/String/String.cpp 13.49/String/String.h)
target_include_directories(String_3 PUBLIC 13.49/String)

add_library(String_4 STATIC 13.50/String/String.cpp 13.50/String/String.h)
target_include_directories(String_4 PUBLIC 13.50/String)

add_executable(13.50_13.48 13.50/13.48.cpp)
target_link_libraries(13.50_13.48 PUBLIC String_4)

add_library(HasPtr_5 INTERFACE)
target_include_directories(HasPtr_5 INTERFACE 13.53/HasPtr_operator_assign)

add_library(HasPtr_6 INTERFACE)
target_include_directories(HasPtr_6 INTERFACE 13.53/HasPtr_swap_assign)

add_library(HasPtr_7 INTERFACE)
target_include_directories(HasPtr_7 INTERFACE 13.54/HasPtr)

add_executable(13.54 13.54/main.cpp)
target_link_libraries(13.54 PUBLIC HasPtr_7)

add_library(StrBlob_5 STATIC 13.55/StrBlob.cpp 13.55/StrBlob.h)
target_include_directories(StrBlob_5 PUBLIC 13.55)

add_executable(13.58_13.56 13.58/13.56.cpp)
add_executable(13.58_13.57 13.58/13.57.cpp)
