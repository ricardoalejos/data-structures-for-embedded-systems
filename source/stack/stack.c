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

#include "stack.h"
#include <string.h>

#define PRV__M_TRY_SEM_TAKE(iStackPtr)                                        \
    if(iStackPtr->vSemaphoreInterface->fTake(iStackPtr->vSemaphore) != 0)     \
        return STACK__C_ERROR_SEMAPHORE_TAKE


#define PRV__M_TRY_SEM_GIVE(iStackPtr)                                        \
    if(iStackPtr->vSemaphoreInterface->fGive(iStackPtr->vSemaphore) != 0)     \
        return STACK__C_ERROR_SEMAPHORE_GIVE

#define PRV__M_CHECK_NULL(iPointer)                                           \
    if(!iPointer)                                                             \
        return STACK__C_ERROR_IS_NULL

#define PRV__M_INDEX_BYTE(iBuffer, iIndex)  (((uint8_t *)iBuffer)[iIndex])


Stack_tRetVal Stack_fIsStackFull(Stack_t * iStack)
{
    PRV__M_CHECK_NULL(iStack);

    if(iStack->vCount == iStack->vLength)
        return STACK__C_TRUE;
    else
        return STACK__C_FALSE;
}


Stack_tRetVal Stack_fIsStackEmpty(Stack_t * iStack)
{
    PRV__M_CHECK_NULL(iStack);

    if(iStack->vCount == 0)
        return STACK__C_TRUE;
    else
        return STACK__C_FALSE;
}


Stack_tRetVal Stack_fPush(Stack_t * iStack, void * iDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vBufferIndex;

    PRV__M_CHECK_NULL(iStack);

    if(Stack_fIsStackFull(iStack) == STACK__C_TRUE)
        return STACK__C_ERROR_STACK_IS_FULL;

    if(iStack->vLength - iStack->vCount < iDataBufferSize)
        return STACK__C_ERROR_DATA_DOES_NOT_FIT;

    PRV__M_TRY_SEM_TAKE(iStack);

    for(vBufferIndex = 0; vBufferIndex < iDataBufferSize; vBufferIndex++)
    {
        PRV__M_INDEX_BYTE(iStack->vData, iStack->vCount) = PRV__M_INDEX_BYTE(iDataBuffer, vBufferIndex);
        iStack->vCount++;
    }

    PRV__M_TRY_SEM_GIVE(iStack);
    return STACK__C_SUCCESS;
}


Stack_tRetVal Stack_fPop(Stack_t * iStack, void * oDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vBufferIndex;

    PRV__M_CHECK_NULL(iStack);

    if(Stack_fIsStackEmpty(iStack) == STACK__C_TRUE)
        return STACK__C_ERROR_STACK_IS_EMPTY;

    if(iStack->vCount < iDataBufferSize)
        return STACK__C_ERROR_NOT_ENOUGH_DATA;

    PRV__M_TRY_SEM_TAKE(iStack);

    for(vBufferIndex = 0; vBufferIndex < iDataBufferSize; vBufferIndex++)
    {
        PRV__M_INDEX_BYTE(oDataBuffer, vBufferIndex) = PRV__M_INDEX_BYTE(iStack->vData, iStack->vCount - 1);
        iStack->vCount--;
    }

    PRV__M_TRY_SEM_GIVE(iStack);
    return STACK__C_SUCCESS;
}


Stack_tRetVal Stack_fPeek(Stack_t * iStack, void * oDataBuffer, uint32_t iDataBufferSize)
{
    uint32_t vBufferIndex;
    uint32_t vTemporalCount;

    PRV__M_CHECK_NULL(iStack);

    if(Stack_fIsStackEmpty(iStack) == STACK__C_TRUE)
        return STACK__C_ERROR_STACK_IS_EMPTY;

    if(iStack->vCount < iDataBufferSize)
        return STACK__C_ERROR_NOT_ENOUGH_DATA;

    PRV__M_TRY_SEM_TAKE(iStack);

    vTemporalCount = iStack->vCount;

    for(vBufferIndex = 0; vBufferIndex < iDataBufferSize; vBufferIndex++)
    {
        PRV__M_INDEX_BYTE(oDataBuffer, vBufferIndex) = PRV__M_INDEX_BYTE(iStack->vData, vTemporalCount - 1);
        vTemporalCount--;
    }

    PRV__M_TRY_SEM_GIVE(iStack);
    return STACK__C_SUCCESS;
}


Stack_tRetVal Stack_fClear(Stack_t * iStack)
{
    PRV__M_CHECK_NULL(iStack);
    PRV__M_TRY_SEM_TAKE(iStack);

    memset(iStack->vData, 0x00, iStack->vLength);

    PRV__M_TRY_SEM_GIVE(iStack);
    return STACK__C_SUCCESS;
}


Stack_tRetVal Stack_fGetCount(Stack_t * iStack, uint32_t * oCount)
{
    PRV__M_CHECK_NULL(iStack);

    *oCount = iStack->vCount;

    return STACK__C_SUCCESS;
}
