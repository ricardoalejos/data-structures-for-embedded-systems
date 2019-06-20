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

#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>

typedef enum Stack_tRetVal
{
    STACK__C_SUCCESS,
    STACK__C_FAIL,
    STACK__C_TRUE,
    STACK__C_FALSE,
    STACK__C_ERROR_IS_NULL,
    STACK__C_ERROR_SEMAPHORE_GIVE,
    STACK__C_ERROR_SEMAPHORE_TAKE,
    STACK__C_ERROR_STACK_IS_EMPTY,
    STACK__C_ERROR_STACK_IS_FULL,
    STACK__C_ERROR_NOT_ENOUGH_DATA,
    STACK__C_ERROR_DATA_DOES_NOT_FIT
} Stack_tRetVal;

typedef uint32_t (*Stack_tSemaphoreCallback)(void * iSemaphore);

typedef struct Stack_sSemaphoreInterface
{
    Stack_tSemaphoreCallback fTake;
    Stack_tSemaphoreCallback fGive;
} Stack_tSemaphoreInterface;

typedef struct Stack_s
{
    const uint32_t vLength;
    volatile uint32_t vCount;
    void * vData;
    void * vSemaphore;
    Stack_tSemaphoreInterface * vSemaphoreInterface;
} Stack_t;

Stack_tRetVal Stack_fPush(Stack_t * iStack, void * iDataBuffer, uint32_t iDataBufferSize);
Stack_tRetVal Stack_fPop(Stack_t * iStack, void * oDataBuffer, uint32_t iDataBufferSize);
Stack_tRetVal Stack_fPeek(Stack_t * iStack, void * oDataBuffer, uint32_t iDataBufferSize);
Stack_tRetVal Stack_fClear(Stack_t * iStack);
Stack_tRetVal Stack_fIsStackFull(Stack_t * iStack);
Stack_tRetVal Stack_fIsStackEmpty(Stack_t * iStack);
Stack_tRetVal Stack_fGetCount(Stack_t * iStack, uint32_t * oCount);

#endif /* _STACK_H_ */
