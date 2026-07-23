cmake_minimum_required(VERSION 3.16)
project(day03_exti C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(exti_core drivers/exti/exti_button_core.c)
target_include_directories(exti_core PUBLIC drivers/exti)

add_executable(exti_button_sim
    examples/03-exti-button-interrupt/host_simulation.c)
target_link_libraries(exti_button_sim PRIVATE exti_core)

enable_testing()
add_executable(test_exti tests/test_exti_button_core.c)
target_link_libraries(test_exti PRIVATE exti_core)
add_test(NAME exti_button_tests COMMAND test_exti)
