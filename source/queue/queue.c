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

#include "queue.h"
#include <string.h>

#define PRV__M_TRY_SEM_TAKE(iQueuePtr)                                        \
    if(iQueuePtr->vSemaphoreInterface->fTake(iQueuePtr->vSemaphore) != 0)     \
        return QUEUE__C_ERROR_SEMAPHORE_TAKE


#define PRV__M_TRY_SEM_GIVE(iQueuePtr)                                        \
    if(iQueuePtr->vSemaphoreInterface->fGive(iQueuePtr->vSemaphore) != 0)     \
        return QUEUE__C_ERROR_SEMAPHORE_GIVE

#define PRV__M_CHECK_NULL(iPointer)                                           \
    if(!iPointer)                                                             \
        return QUEUE__C_ERROR_IS_NULL

#define PRV__M_INDEX_BYTE(iBuffer, iIndex)  (((uint8_t *)iBuffer)[iIndex])


Queue_tRetVal Queue_fIsQueueFull(Queue_t * iQueue)
{
    PRV__M_CHECK_NULL(iQueue);

    if (iQueue->vCount >= iQueue->vLength)
        return QUEUE__C_TRUE;
    else
        return QUEUE__C_FALSE;
}


Queue_tRetVal Queue_fIsQueueEmpty(Queue_t * iQueue)
{
    PRV__M_CHECK_NULL(iQueue);

    if (iQueue->vCount == 0)
        return QUEUE__C_TRUE;
    else
        return QUEUE__C_FALSE;
}


Queue_tRetVal Queue_fPut(Queue_t * iQueue, void * iDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vDataBufferIndex;

    PRV__M_CHECK_NULL(iQueue);
    PRV__M_CHECK_NULL(iDataBuffer);
    PRV__M_TRY_SEM_TAKE(iQueue);

    if (Queue_fIsQueueFull(iQueue) == QUEUE__C_TRUE)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_QUEUE_IS_FULL;
    }

    if (iQueue->vLength - iQueue->vCount < iDataBufferSize)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_DATA_DOES_NOT_FIT;
    }

    for(vDataBufferIndex = 0; vDataBufferIndex < iDataBufferSize; vDataBufferIndex++)
    {
        PRV__M_INDEX_BYTE(iQueue->vData, iQueue->vPutIndex) = PRV__M_INDEX_BYTE(iDataBuffer, vDataBufferIndex);
        iQueue->vPutIndex++;
        iQueue->vPutIndex %= iQueue->vLength;
    }

    iQueue->vCount += iDataBufferSize;

    PRV__M_TRY_SEM_GIVE(iQueue);

    return QUEUE__C_SUCESS;
}


Queue_tRetVal Queue_fGet(Queue_t * iQueue, void * oDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vDataBufferIndex;

    PRV__M_CHECK_NULL(iQueue);
    PRV__M_CHECK_NULL(oDataBuffer);
    PRV__M_TRY_SEM_TAKE(iQueue);

    if (Queue_fIsQueueEmpty(iQueue) == QUEUE__C_TRUE)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_QUEUE_IS_EMPTY;
    }

    if (iQueue->vCount < iDataBufferSize)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_NOT_ENOUGH_DATA;
    }

    for(vDataBufferIndex = 0; vDataBufferIndex < iDataBufferSize; vDataBufferIndex++)
    {
        PRV__M_INDEX_BYTE(oDataBuffer, vDataBufferIndex) = PRV__M_INDEX_BYTE(iQueue->vData, iQueue->vGetIndex);
        iQueue->vGetIndex++;
        iQueue->vGetIndex %= iQueue->vLength;
    }

    iQueue->vCount -= iDataBufferSize;

    PRV__M_TRY_SEM_GIVE(iQueue);

    return QUEUE__C_SUCESS;
}


Queue_tRetVal Queue_fClear(Queue_t * iQueue)
{
    PRV__M_CHECK_NULL(iQueue);
    PRV__M_TRY_SEM_TAKE(iQueue);

    memset(iQueue->vData, 0x00, iQueue->vLength);
    iQueue->vPutIndex = 0;
    iQueue->vGetIndex = 0;
    iQueue->vCount = 0;

    PRV__M_TRY_SEM_GIVE(iQueue);
    return QUEUE__C_SUCESS;
}


Queue_tRetVal Queue_fPeek(Queue_t * iQueue, void * oDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vDataBufferIndex;
    uint32_t vTempGetIndex;

    PRV__M_CHECK_NULL(iQueue);
    PRV__M_CHECK_NULL(oDataBuffer);
    PRV__M_TRY_SEM_TAKE(iQueue);

    if (Queue_fIsQueueEmpty(iQueue) == QUEUE__C_TRUE)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_QUEUE_IS_EMPTY;
    }

    if (iQueue->vCount < iDataBufferSize)
    {
        PRV__M_TRY_SEM_GIVE(iQueue);
        return QUEUE__C_ERROR_NOT_ENOUGH_DATA;
    }

    vTempGetIndex = iQueue->vGetIndex;

    for(vDataBufferIndex = 0; vDataBufferIndex < iDataBufferSize; vDataBufferIndex++)
    {
        PRV__M_INDEX_BYTE(oDataBuffer, vDataBufferIndex) = PRV__M_INDEX_BYTE(iQueue->vData, vTempGetIndex);
        vTempGetIndex++;
        vTempGetIndex %= iQueue->vLength;
    }

    PRV__M_TRY_SEM_GIVE(iQueue);

    return QUEUE__C_SUCESS;
}


Queue_tRetVal Queue_fGetCount(Queue_t * iQueue, uint32_t * oCount)
{
    PRV__M_CHECK_NULL(iQueue);
    PRV__M_CHECK_NULL(oCount);

    *oCount = iQueue->vCount;

    return QUEUE__C_SUCESS;
}


Queue_tRetVal Queue_fGetCapacity(Queue_t * iQueue, uint32_t * oCapacity)
{
    PRV__M_CHECK_NULL(iQueue);
    PRV__M_CHECK_NULL(oCapacity);

    *oCapacity = iQueue->vLength - iQueue->vCount;

    return QUEUE__C_SUCESS;
}
