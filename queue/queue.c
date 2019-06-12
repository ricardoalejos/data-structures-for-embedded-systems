/*
 * queues.c
 *
 *  Created on: 16 abr 2019
 *      Author: ricardo
 */

#include "queue.h"
#include <string.h>




queue_ret_t queue_is_full(queue_t * queue, bool * response)
{
    if(queue == NULL)
        return QUEUE_FAIL;

    if (queue->queue_size >= queue->queue_capacity)
        *response = true;
    else
        *response = false;

    return QUEUE_SUCCESS;
}


queue_ret_t queue_is_empty(queue_t * queue, bool * response)
{
    if(queue == NULL)
        return QUEUE_FAIL;

    if (queue->queue_size == 0)
        *response = true;
    else
        *response = false;

    return QUEUE_SUCCESS;
}


queue_ret_t queue_put(queue_t * queue, void * item_buffer, size_t item_size)
{
    void * result;
    bool is_full;
    uint32_t put_index;

    if(queue == NULL || item_size > queue->element_size)
        return QUEUE_FAIL;

    queue_is_full(queue, &is_full);

    if(is_full)
        return QUEUE_FAIL;

    put_index = (queue->get_index + queue->queue_size) % queue->queue_capacity;

    result = memcpy(
            (void *) &queue->buffer[put_index * queue->element_size],
            item_buffer,
            item_size);

    if(result == NULL)
        return QUEUE_FAIL;

    queue->queue_size++;

    return QUEUE_SUCCESS;
}


queue_ret_t queue_get(queue_t * queue, void * item_buffer, size_t item_size)
{
    void * result;
    bool is_empty;

    if(queue == NULL || item_size > queue->element_size)
        return QUEUE_FAIL;

    queue_is_empty(queue, &is_empty);

    if(is_empty)
        return QUEUE_FAIL;

    result = memcpy(
            item_buffer,
            (void *) &queue->buffer[queue->get_index * queue->element_size],
            item_size);

    if(result == NULL)
        return QUEUE_FAIL;

    result = memset(
    		(void *) &queue->buffer[queue->get_index * queue->element_size],
			0,
			queue->element_size);

    if(result == NULL)
		return QUEUE_FAIL;

    queue->get_index = (queue->get_index + 1) % queue->queue_capacity;
    queue->queue_size--;

    return QUEUE_SUCCESS;
}


queue_ret_t queue_clear(queue_t * queue)
{
    void * result;

    if(queue == NULL)
        return QUEUE_FAIL;

    result = memset(
            (void *) queue->buffer,
            0,
            queue->element_size * queue->queue_capacity);

    if(result == NULL)
            return QUEUE_FAIL;

    queue->queue_size = 0;
	queue->get_index = 0;

    return QUEUE_SUCCESS;
}
