/*
 * stack.h
 *
 *  Created on: Apr 17, 2019
 *      Author: ricardo
 */

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
