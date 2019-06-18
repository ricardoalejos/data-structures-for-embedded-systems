file(GLOB source_files "./*.c")
add_executable(test ${source_files})
target_link_libraries(test queue stack)
