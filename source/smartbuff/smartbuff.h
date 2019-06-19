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

#ifndef _SMARTBUFF_H_
#define _SMARTBUFF_H_

#include <stdint.h>


typedef enum SmaBuf_eRetVal
{
    SMA_BUF__C_SUCCESS,
    SMA_BUF__C_FAIL,
    SMA_BUF__C_ERROR_TARGET_READ,
    SMA_BUF__C_ERROR_TARGET_WRITE,
    SMA_BUF__C_ERROR_SEMAPHORE_TAKE,
    SMA_BUF__C_ERROR_SEMAPHORE_GIVE,
    SMA_BUF__C_ERROR_BUFFER_DOES_NOT_FIT,
    SMA_BUF__C_ERROR_DATA_DOES_NOT_FIT,
    SMA_BUF__C_ERROR_TARGET_ADDRESS_TOO_HIGH,
    SMA_BUF__C_ERROR_BUFFER_OFFSET_TOO_HIGH
} SmaBuf_tRetVal;

/* Interface functions are expected to return 0 if they run succesfully. Else,
 * it is assumed that they ran into an error or failed. */
typedef uint32_t (*SmaBuf_tTargetIoCallback)(uint32_t iAddress, void * ioDataBuffer, uint32_t iDataBufferSize);
typedef uint32_t (*SmaBuf_tSemaphoreCallback)(void * iSemaphore);

typedef struct SmaBuf_sTargetInterface
{
    SmaBuf_tTargetIoCallback fRead;
    SmaBuf_tTargetIoCallback fWrite;
} SmaBuf_tTargetInterface;

typedef struct SmaBuf_sSemaphoreInterface
{
    SmaBuf_tSemaphoreCallback fGive;
    SmaBuf_tSemaphoreCallback fTake;
} SmaBuf_tSemaphoreInterface;

typedef struct SmaBuf_s
{
    uint32_t vTargetBaseAddress;
    uint32_t vBufferOffset;
    const uint32_t vBufferSize;
    const uint32_t vTargetSize;
    void * vData;
    void * vSemaphore;
    const SmaBuf_tTargetInterface * vTargetInterface;
    const SmaBuf_tSemaphoreInterface * vSemaphoreInterface;
} SmaBuf_t;

#define SMA_BUF__V_DATA_INITIALIZER(size, fill) ((void *)((uint8_t [size]){fill}))

SmaBuf_tRetVal SmaBuf_fWriteToTarget(SmaBuf_t * iSmaBuf);
SmaBuf_tRetVal SmaBuf_fReadFromTarget(SmaBuf_t * iSmaBuf);
SmaBuf_tRetVal SmaBuf_fWriteData(SmaBuf_t * iSmaBuf, void * iDataBuffer, uint32_t iDataBufferSize);
SmaBuf_tRetVal SmaBuf_fReadData(SmaBuf_t * iSmaBuf, void * oDataBuffer, uint32_t iDataBufferSize);
SmaBuf_tRetVal SmaBuf_fSetTargetBaseAddress(SmaBuf_t * iSmaBuf, uint32_t iTargetBaseAddress);
SmaBuf_tRetVal SmaBuf_fGetTargetBaseAddress(SmaBuf_t * iSmaBuf, uint32_t * oTargetBaseAddress);
SmaBuf_tRetVal SmaBuf_fSetBufferOffset(SmaBuf_t * iSmaBuf, uint32_t iBufferOffset);
SmaBuf_tRetVal SmaBuf_fGetBufferOffset(SmaBuf_t * iSmaBuf, uint32_t * oBufferOffset);

#endif
