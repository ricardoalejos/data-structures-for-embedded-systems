file(GLOB source_files "./*.c")
add_executable(gpio_example ${source_files})
target_link_libraries(gpio_example gpio)
