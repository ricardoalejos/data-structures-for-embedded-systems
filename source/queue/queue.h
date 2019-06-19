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

#ifndef QUEUE_QUEUES_H_
#define QUEUE_QUEUES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct queue_s
{
    volatile uint32_t queue_size;
    volatile uint32_t get_index;
    const size_t element_size;
    const uint32_t queue_capacity;
    volatile uint8_t * buffer;
} queue_t;

typedef enum queue_ret_e
{
    QUEUE_SUCCESS,
    QUEUE_FAIL
} queue_ret_t;

#define QUEUE_INITIALIZE(e_size, q_capacity)  {             \
    .element_size = e_size,                                 \
    .queue_capacity = q_capacity,                           \
    .queue_size = 0,                                        \
    .get_index = 0,                                         \
    .buffer = (volatile uint8_t [e_size * q_capacity]){0}}

#define QUEUE_INITIALIZE_WITH_VALUES(e_size, q_capacity, n_items, ...) {    \
    .element_size = e_size,                                                 \
    .queue_capacity = q_capacity,                                           \
    .queue_size = n_items,                                                  \
    .get_index = 0,                                                         \
    .buffer = (volatile uint8_t [e_size * q_capacity]){__VA_ARGS__}}

queue_ret_t queue_is_full(queue_t * queue, bool * response);
queue_ret_t queue_is_empty(queue_t * queue, bool * response);
queue_ret_t queue_put(queue_t * queue, void * item_buffer, size_t item_size);
queue_ret_t queue_get(queue_t * queue, void * item_buffer, size_t item_size);
queue_ret_t queue_clear(queue_t * queue);

#endif /* QUEUE_QUEUES_H_ */
