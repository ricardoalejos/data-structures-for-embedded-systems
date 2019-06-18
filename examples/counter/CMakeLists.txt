file(GLOB source_files "./*.c")
add_executable(counter_example ${source_files})
target_link_libraries(counter_example counter)
