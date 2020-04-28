add_library(Quote INTERFACE)
target_include_directories(Quote INTERFACE 15.3)

add_library(Bulk_quote INTERFACE)
target_link_libraries(Bulk_quote INTERFACE Quote)
target_include_directories(Bulk_quote INTERFACE 15.5)

add_executable(15.6 15.6.cpp)
target_link_libraries(15.6 PUBLIC Quote PUBLIC Bulk_quote)

add_library(Limited_bulk_quote INTERFACE)
target_link_libraries(Limited_bulk_quote INTERFACE Bulk_quote)
target_include_directories(Limited_bulk_quote INTERFACE 15.7)
