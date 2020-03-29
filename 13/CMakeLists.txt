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
