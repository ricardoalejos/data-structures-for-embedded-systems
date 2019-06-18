cmake_minimum_required (VERSION 2.6)
project (DSFES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "-O0 -ggdb")
set(project_root ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(".")

add_subdirectory(queue)
add_subdirectory(stack)
add_subdirectory(gpio)
add_subdirectory(counter)
add_subdirectory(semaphore)
add_subdirectory(examples)
