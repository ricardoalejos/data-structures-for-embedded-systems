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

#ifndef _QUEUES_H_
#define _QUEUES_H_

#include <stdint.h>

typedef enum Queue_eRetVal
{
    QUEUE__C_SUCESS,
    QUEUE__C_FAIL,
    QUEUE__C_TRUE,
    QUEUE__C_FALSE,
    QUEUE__C_ERROR_QUEUE_IS_FULL,
    QUEUE__C_ERROR_QUEUE_IS_EMPTY,
    QUEUE__C_ERROR_IS_NULL,
    QUEUE__C_ERROR_SEMAPHORE_TAKE,
    QUEUE__C_ERROR_SEMAPHORE_GIVE,
    QUEUE__C_ERROR_DATA_DOES_NOT_FIT,
    QUEUE__C_ERROR_NOT_ENOUGH_DATA
} Queue_tRetVal;

typedef uint32_t (* Queue_tSemaphoreCallback)(void * iSemaphore);

typedef struct Queue_sSemaphoreInterface
{
    Queue_tSemaphoreCallback fTake;
    Queue_tSemaphoreCallback fGive;
} Queue_tSemaphoreInterface;

typedef struct Queue_s
{
    const uint32_t vLength;
    volatile uint32_t vCount;
    volatile uint32_t vPutIndex;
    volatile uint32_t vGetIndex;
    void * vData;
    const Queue_tSemaphoreInterface * vSemaphoreInterface;
    void * vSemaphore;
} Queue_t;

#define QUEUE__M_DATA_INITIALIZER(size, fill) ((void *)((uint8_t [size]){fill}))

Queue_tRetVal Queue_fIsQueueFull(Queue_t * iQueue);
Queue_tRetVal Queue_fIsQueueEmpty(Queue_t * iQueue);
Queue_tRetVal Queue_fClear(Queue_t * iQueue);
Queue_tRetVal Queue_fGetCount(Queue_t * iQueue, uint32_t * oCount);
Queue_tRetVal Queue_fGetCapacity(Queue_t * iQueue, uint32_t * oCapacity);
Queue_tRetVal Queue_fPut(Queue_t * iQueue, void * iDataBuffer, uint32_t iDataBufferSize);
Queue_tRetVal Queue_fGet(Queue_t * iQueue, void * oDataBuffer, uint32_t iDataBufferSize);
Queue_tRetVal Queue_fPeek(Queue_t * iQueue, void * oDataBuffer, uint32_t iDataBufferSize);


#endif /* _QUEUES_H_ */
