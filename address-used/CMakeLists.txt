add_executable(add_used addused.c)
target_link_libraries(add_used network)

add_executable(add_reused addreused.c)
target_link_libraries(add_reused network)