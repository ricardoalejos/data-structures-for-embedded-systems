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

#include "stack/stack.h"
#include <stdio.h>

#define C_STACK_SIZE          42
#define C_PEEK_SIZE           7

uint32_t fStackTests();
uint32_t fFillStack(Stack_t * iStack);
uint32_t fDumpStack(Stack_t * iStack);
uint32_t fShowStackTop(Stack_t * iStack, uint32_t iBytesToShow);
uint32_t fFakeSemaphoreTake(void * iSemaphore);
uint32_t fFakeSemaphoreGive(void * iSemaphore);


int main(int argc, char ** argv)
{
    fStackTests();
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


uint32_t fStackTests()
{
    Stack_tSemaphoreInterface vFakeSemaphoreInterface = {
        .fTake = fFakeSemaphoreTake,
        .fGive = fFakeSemaphoreGive
    };

    Stack_t vExampleStack = {
        .vLength = C_STACK_SIZE,
        .vCount = 0,
        .vData = (void*)((uint8_t [C_STACK_SIZE]){0}),
        .vSemaphore = (void *) 0,
        .vSemaphoreInterface = &vFakeSemaphoreInterface
    };

    // Push data to stack
    fFillStack(&vExampleStack);

    // Verify if the stack is full
    if(Stack_fIsStackFull(&vExampleStack) == STACK__C_TRUE)
        puts("The stack is full.");

    // Check what is at the top of the stack
    fShowStackTop(&vExampleStack, C_PEEK_SIZE);

    // Pop the data from the stack
    fDumpStack(&vExampleStack);

    // Verify the stack is empty
    if(Stack_fIsStackEmpty(&vExampleStack) == STACK__C_TRUE)
        puts("The stack is empty.");

    return 0;
}


uint32_t fFillStack(Stack_t * iStack)
{
    uint8_t vInputCharacter;

    vInputCharacter = '0';
    printf("Pushing into the stack: ");
    while(Stack_fIsStackFull(iStack) != STACK__C_TRUE)
    {
        Stack_fPush(iStack, &vInputCharacter, 1);
        putc(vInputCharacter, stdout);
        vInputCharacter++;
    }
    printf("\n");

    return 0;
}


uint32_t fDumpStack(Stack_t * iStack)
{
    uint32_t vOutputCharacter;

    printf("Popping out of the stack: ");
    while(Stack_fIsStackEmpty(iStack) != STACK__C_TRUE)
    {
        Stack_fPop(iStack, &vOutputCharacter, 1);
        putc(vOutputCharacter, stdout);
    }
    printf("\n");
}


uint32_t fShowStackTop(Stack_t * iStack, uint32_t iBytesToShow)
{
    uint8_t vOutputBuffer[C_STACK_SIZE];
    uint32_t vCurrentStackCount;
    uint32_t vBufferIndex;

    Stack_fGetCount(iStack, &vCurrentStackCount);

    if (iBytesToShow > vCurrentStackCount)
        return 1;

    Stack_fPeek(iStack, (void *) vOutputBuffer, iBytesToShow);

    printf("The top %d elements in the stack are: ", iBytesToShow);
    vBufferIndex = 0;
    while(vBufferIndex < iBytesToShow)
    {
        putc(vOutputBuffer[vBufferIndex++], stdout);
    }
    printf("\n");

    return 0;
}