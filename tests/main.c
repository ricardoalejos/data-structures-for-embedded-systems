/*
 * main.c
 *
 *  Created on: 16 abr 2019
 *      Author: ricardo
 */

#include "queue/queue.h"
#include "stack/stack.h"
#include <stdio.h>


queue_t my_queue = QUEUE_INITIALIZE(4, 3);
stack_t my_stack = STACK_INITIALIZE(4, 3);

// queue_t my_queue = QUEUE_INITIALIZE_WITH_VALUES(4,3,1,0xdeadbeef);

int main(int argc, char ** argv)
{
    bool response;
    uint32_t test;

    printf("Executing data_structures.\n");

    queue_put(&my_queue, (uint8_t[4]){0xba, 0xca, 0xca, 0xfe}, 4);
    queue_put(&my_queue, (uint8_t[4]){0x1, 0x2, 0x3, 0x4}, 4);
    queue_put(&my_queue, (uint8_t[4]){0x5, 0x6, 0x7, 0x8}, 4);
    queue_put(&my_queue, (uint8_t[4]){0x9, 0xa, 0xb, 0xc}, 4);
    queue_is_empty(&my_queue, &response);
    printf("queue_is_empty: %d (size = %d).\n", response, my_queue.queue_size);

    queue_get(&my_queue, &test, 4);
    printf("queue_get: %x (size = %d).\n", test, my_queue.queue_size);
    queue_get(&my_queue, &test, 4);
    printf("queue_get: %x (size = %d).\n", test, my_queue.queue_size);
    queue_get(&my_queue, &test, 4);
    printf("queue_get: %x (size = %d).\n", test, my_queue.queue_size);
    queue_get(&my_queue, &test, 4);
    printf("queue_get: %x (size = %d).\n", test, my_queue.queue_size);


    stack_push(&my_stack, (uint8_t[4]){1,2,3,4}, 4);
    stack_push(&my_stack, (uint8_t[4]){5,6,7,8}, 4);
    stack_push(&my_stack, (uint8_t[4]){9,8,7,6}, 4);
    stack_push(&my_stack, (uint8_t[4]){5,4,3,2}, 4);
    stack_pop(&my_stack, &test, 4);
	printf("stack_pop: %x (size = %d).\n", test, my_stack.stack_size);
	stack_pop(&my_stack, &test, 4);
	printf("stack_pop: %x (size = %d).\n", test, my_stack.stack_size);
	stack_pop(&my_stack, &test, 4);
	printf("stack_pop: %x (size = %d).\n", test, my_stack.stack_size);
	stack_pop(&my_stack, &test, 4);
	printf("stack_pop: %x (size = %d).\n", test, my_stack.stack_size);

    return 0;
}
