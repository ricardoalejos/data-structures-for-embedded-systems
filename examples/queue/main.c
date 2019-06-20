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

#include "queue/queue.h"
#include <stdio.h>

#define C_QUEUE_SIZE          32
#define C_TEST_MESSAGE        "Hello queues!"
#define C_ACCESS_SIZE         4

uint32_t fQueueTests();
uint32_t fFakeSemaphoreTake(void * iSemaphore);
uint32_t fFakeSemaphoreGive(void * iSemaphore);


int main(int argc, char ** argv)
{
    fQueueTests();
    return 0;
}


uint32_t fFakeSemaphoreTake(void * iSemaphore)
{
    return 0;
}


uint32_t fFakeSemaphoreGive(void * iSemaphore)
{
    return 0;
}


uint32_t fQueueTests()
{
    Queue_tSemaphoreInterface vFakeSemaphoreInterface = {
        .fTake = fFakeSemaphoreTake,
        .fGive = fFakeSemaphoreGive
    };

    Queue_t vExampleQueue = {
        .vLength = C_QUEUE_SIZE,
        .vCount = 0,
        .vPutIndex = 0,
        .vGetIndex = 0,
        .vData = (void*)((uint8_t [C_QUEUE_SIZE]){0}),
        .vSemaphore = (void *) 0,
        .vSemaphoreInterface = &vFakeSemaphoreInterface
    };

    uint8_t vInputBuffer[] = C_TEST_MESSAGE;
    uint8_t vOutputBuffer[sizeof(vInputBuffer)];
    uint8_t vAuxiliarIndex;
    Queue_tRetVal vRetVal;

    // Send data through the queue
    for (vAuxiliarIndex = 0; vAuxiliarIndex < sizeof(vInputBuffer); vAuxiliarIndex+=C_ACCESS_SIZE)
        vRetVal = Queue_fPut(&vExampleQueue, &(vInputBuffer[vAuxiliarIndex]), C_ACCESS_SIZE);

    // Verify if the queue is full
    if(Queue_fIsQueueFull(&vExampleQueue) == QUEUE__C_TRUE)
        puts("The queue is full.");

    // See the tip of the queue
    vRetVal = Queue_fPeek(&vExampleQueue, (void *)vOutputBuffer, C_ACCESS_SIZE); 
    for (vAuxiliarIndex = 0; vAuxiliarIndex < C_ACCESS_SIZE; vAuxiliarIndex++)
        putc(vOutputBuffer[vAuxiliarIndex], stdout);
    putc('\n', stdout);

    // Get the data from the queue
    for (vAuxiliarIndex = 0; vAuxiliarIndex < sizeof(vInputBuffer); vAuxiliarIndex+=C_ACCESS_SIZE)
        vRetVal = Queue_fGet(&vExampleQueue, &(vOutputBuffer[vAuxiliarIndex]), C_ACCESS_SIZE); 

    // Verify it is empty
    if(Queue_fIsQueueEmpty(&vExampleQueue) == QUEUE__C_TRUE)
        puts("The queue is empty.");

    printf("%s\n", vOutputBuffer);

    return (uint32_t) vRetVal;
}
