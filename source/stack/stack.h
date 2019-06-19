/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This file is part of the Data Structures For Embedded Systems (DSFES).     *
 * Copyright (c) 2019 Ricardo Alejos <ricardoalejos20@gmail.com>              *
 *                                                                            *
 * DSFES is free software: you can redistribute it and/or modify              *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * DSFES is distributed in the hope that it will be useful,                   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with DSFES.  If not, see <https://www.gnu.org/licenses/>.            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DATA_STRUCTURES_FOR_EMBEDDED_SYSTEMS_STACK_STACK_H_
#define DATA_STRUCTURES_FOR_EMBEDDED_SYSTEMS_STACK_STACK_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct stack_s
{
    volatile uint32_t stack_size;
    const size_t element_size;
    const uint32_t stack_capacity;
    volatile uint8_t * buffer;
} stack_t;

typedef enum stack_ret_e
{
    STACK_SUCCESS,
    STACK_FAIL
} stack_ret_t;

#define STACK_INITIALIZE(e_size, s_capacity)  {             \
    .element_size = e_size,                                 \
    .stack_capacity = s_capacity,                           \
    .stack_size = 0,                                        \
    .buffer = (volatile uint8_t [e_size * s_capacity]){0}}

stack_ret_t stack_is_full(stack_t * stack, bool * response);
stack_ret_t stack_is_empty(stack_t * stack, bool * response);
stack_ret_t stack_push(stack_t * stack, void * item_buffer, size_t item_size);
stack_ret_t stack_pop(stack_t * stack, void * item_buffer, size_t item_size);
stack_ret_t stack_clear(stack_t * stack);

#endif /* DATA_STRUCTURES_FOR_EMBEDDED_SYSTEMS_STACK_STACK_H_ */
