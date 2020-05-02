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
