add_library(Quote INTERFACE)
target_include_directories(Quote INTERFACE 15.3/Quote)

add_library(print_total INTERFACE)
target_link_libraries(print_total INTERFACE Quote)
target_include_directories(print_total INTERFACE 15.3/print_total)

add_library(Bulk_quote INTERFACE)
target_link_libraries(Bulk_quote INTERFACE Quote)
target_include_directories(Bulk_quote INTERFACE 15.5)

add_executable(15.6 15.6.cpp)
target_link_libraries(15.6 PUBLIC print_total PUBLIC Bulk_quote)

add_library(Limit_quote INTERFACE)
target_link_libraries(Limit_quote INTERFACE Quote)
target_include_directories(Limit_quote INTERFACE 15.7)

add_library(Quote_2 INTERFACE)
target_include_directories(Quote_2 INTERFACE 15.11/Quote)

add_library(Bulk_quote_2 INTERFACE)
target_link_libraries(Bulk_quote_2 INTERFACE Quote_2)
target_include_directories(Bulk_quote_2 INTERFACE 15.11/Bulk_quote)

add_library(Limit_quote_2 INTERFACE)
target_link_libraries(Limit_quote_2 INTERFACE Quote_2)
target_include_directories(Limit_quote_2 INTERFACE 15.11/Limit_quote)

add_library(Disc_quote INTERFACE)
target_link_libraries(Disc_quote INTERFACE Quote)
target_include_directories(Disc_quote INTERFACE 15.15/Disc_quote)

add_library(Bulk_quote_3 INTERFACE)
target_link_libraries(Bulk_quote_3 INTERFACE Disc_quote)
target_include_directories(Bulk_quote_3 INTERFACE 15.15/Bulk_quote)

add_library(Limit_quote_3 INTERFACE)
target_link_libraries(Limit_quote_3 INTERFACE Disc_quote)
target_include_directories(Limit_quote_3 INTERFACE 15.16)

add_executable(15.20_15.18 15.20/15.18.cpp)
add_executable(15.20_15.19 15.20/15.19.cpp)

add_library(Quote_3 INTERFACE)
target_include_directories(Quote_3 INTERFACE 15.26/Quote)

add_library(Disc_quote_2 INTERFACE)
target_link_libraries(Disc_quote_2 INTERFACE Quote_3)
target_include_directories(Disc_quote_2 INTERFACE 15.26/Disc_quote)

add_library(Bulk_quote_4 INTERFACE)
target_link_libraries(Bulk_quote_4 INTERFACE Disc_quote_2)
target_include_directories(Bulk_quote_4 INTERFACE 15.26/Bulk_quote)

add_executable(15.26 15.26/main.cpp)
target_link_libraries(15.26 PUBLIC Bulk_quote_4)

add_library(Bulk_quote_5 INTERFACE)
target_link_libraries(Bulk_quote_5 INTERFACE Disc_quote)
target_include_directories(Bulk_quote_5 INTERFACE 15.27)

add_executable(15.28 15.28.cpp)
target_link_libraries(15.28 PUBLIC Bulk_quote_3)

add_executable(15.29 15.29.cpp)
target_link_libraries(15.29 PUBLIC Bulk_quote_3)

add_library(Quote_4 INTERFACE)
target_include_directories(Quote_4 INTERFACE 15.30/Quote)

add_library(Disc_quote_3 INTERFACE)
target_link_libraries(Disc_quote_3 INTERFACE Quote_4)
target_include_directories(Disc_quote_3 INTERFACE 15.30/Disc_quote)

add_library(Bulk_quote_6 INTERFACE)
target_link_libraries(Bulk_quote_6 INTERFACE Disc_quote_3)
target_include_directories(Bulk_quote_6 INTERFACE 15.30/Bulk_quote)

add_library(Limit_quote_4 INTERFACE)
target_link_libraries(Limit_quote_4 INTERFACE Disc_quote_3)
target_include_directories(Limit_quote_4 INTERFACE 15.30/Limit_quote)

add_library(print_total_2 INTERFACE)
target_link_libraries(print_total_2 INTERFACE Quote_4)
target_include_directories(print_total_2 INTERFACE 15.3/print_total)

add_library(Basket INTERFACE)
target_link_libraries(Basket INTERFACE print_total_2)
target_include_directories(Basket INTERFACE 15.30/Basket)

add_executable(15.30 15.30/main.cpp)
target_link_libraries(15.30 PUBLIC Basket PUBLIC Bulk_quote_6 PUBLIC Limit_quote_4)

add_library(Query INTERFACE)
target_link_libraries(Query INTERFACE TextQuery_3)
target_include_directories(Query INTERFACE 15.35)

add_library(Query_2 INTERFACE)
target_link_libraries(Query_2 INTERFACE TextQuery_3)
target_include_directories(Query_2 INTERFACE 15.36/Query)

add_executable(15.36 15.36/main.cpp)
target_link_libraries(15.36 PUBLIC Query_2)
