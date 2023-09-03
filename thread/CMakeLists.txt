add_executable(thread_hello_server helloworld.c)
target_link_libraries(thread_hello_server network)

add_executable(thread_01_server thread01.c echo.c)
target_link_libraries(thread_01_server network)

add_executable(thread_02_server thread02.c echo.c)
target_link_libraries(thread_02_server network)