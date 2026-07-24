cmake_minimum_required(VERSION 3.16)
project(day04_timer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(timer_core
    drivers/timer/periodic_timer_core.c
    drivers/timer/tick_dispatcher.c
)

target_include_directories(timer_core
    PUBLIC
        drivers/timer
)

add_executable(timer_sim
    examples/04-basic-timer-periodic-interrupt/host_simulation.c
)
target_link_libraries(timer_sim PRIVATE timer_core)

enable_testing()

add_executable(test_periodic_timer
    tests/test_periodic_timer_core.c
)
target_link_libraries(test_periodic_timer PRIVATE timer_core)
add_test(NAME periodic_timer_tests COMMAND test_periodic_timer)

add_executable(test_tick_dispatcher
    tests/test_tick_dispatcher.c
)
target_link_libraries(test_tick_dispatcher PRIVATE timer_core)
add_test(NAME tick_dispatcher_tests COMMAND test_tick_dispatcher)
