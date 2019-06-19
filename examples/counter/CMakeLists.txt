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

file(GLOB source_files "./*.c")
add_executable(counter_example ${source_files})
target_link_libraries(counter_example counter)
