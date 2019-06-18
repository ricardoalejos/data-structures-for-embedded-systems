file(GLOB source_files "./*.c")
add_executable(queue_example ${source_files})
target_link_libraries(queue_example queue stack)
