# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# This file is part of the Data Structures For Embedded Systems (DSFES).      #
# Copyright (c) 2019 Ricardo Alejos <ricardoalejos20@gmail.com>               #
#                                                                             #
# DSFES is free software: you can redistribute it and/or modify               #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# (at your option) any later version.                                         #
#                                                                             #
# DSFES is distributed in the hope that it will be useful,                    #
# but WITHOUT ANY WARRANTY; without even the implied warranty of              #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               #
# GNU General Public License for more details.                                #
#                                                                             #
# You should have received a copy of the GNU General Public License           #
# along with DSFES.  If not, see <https://www.gnu.org/licenses/>.             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

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
