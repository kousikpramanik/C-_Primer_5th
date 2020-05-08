add_library(Quote INTERFACE)
target_include_directories(Quote INTERFACE 15.3/Quote)

add_library(print_total INTERFACE)
target_link_libraries(print_total INTERFACE Quote)
target_include_directories(print_total INTERFACE 15.3/print_total)

add_library(Bulk_quote INTERFACE)
target_link_libraries(Bulk_quote INTERFACE Quote)
target_include_directories(Bulk_quote INTERFACE 15.5)

add_executable(15.6 15.6.cpp)
target_link_libraries(15.6 PUBLIC Quote PUBLIC Bulk_quote PUBLIC print_total)

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
target_link_libraries(15.26 PUBLIC Quote_3 PUBLIC Bulk_quote_4)
