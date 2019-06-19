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

#include "smartbuff/smartbuff.h"
#include <string.h>


#define PRV__M_TRY_SEM_TAKE(iSmaBufPtr)                                       \
    if(iSmaBufPtr->vSemaphoreInterface->fTake(iSmaBufPtr->vSemaphore) != 0)   \
        return SMA_BUF__C_ERROR_SEMAPHORE_TAKE


#define PRV__M_TRY_SEM_GIVE(iSmaBufPtr)                                       \
    if(iSmaBufPtr->vSemaphoreInterface->fGive(iSmaBufPtr->vSemaphore) != 0)   \
        return SMA_BUF__C_ERROR_SEMAPHORE_GIVE


SmaBuf_tRetVal SmaBuf_fWriteToTarget(SmaBuf_t * iSmaBuf)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iSmaBuf->vBufferSize > iSmaBuf->vTargetSize - iSmaBuf->vTargetBaseAddress)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_BUFFER_DOES_NOT_FIT;
    }

    if(iSmaBuf->vTargetInterface->fWrite(iSmaBuf->vTargetBaseAddress, iSmaBuf->vData, iSmaBuf->vBufferSize) != 0)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_TARGET_WRITE;
    }

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fReadFromTarget(SmaBuf_t * iSmaBuf)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iSmaBuf->vBufferSize > iSmaBuf->vTargetSize - iSmaBuf->vTargetBaseAddress)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_BUFFER_DOES_NOT_FIT;
    }

    if(iSmaBuf->vTargetInterface->fRead(iSmaBuf->vTargetBaseAddress, iSmaBuf->vData, iSmaBuf->vBufferSize) != 0)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_TARGET_READ;
    }

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fWriteData(SmaBuf_t * iSmaBuf, void * iDataBuffer, uint32_t iDataBufferSize)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iDataBufferSize > iSmaBuf->vBufferSize - iSmaBuf->vBufferOffset)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_DATA_DOES_NOT_FIT;
    }

    memcpy(
        (void *) &(((uint8_t *)iSmaBuf->vData)[iSmaBuf->vBufferOffset]), 
        iDataBuffer, 
        iDataBufferSize);

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fReadData(SmaBuf_t * iSmaBuf, void * oDataBuffer, uint32_t iDataBufferSize)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iDataBufferSize > iSmaBuf->vBufferSize - iSmaBuf->vBufferOffset)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_DATA_DOES_NOT_FIT;
    }

    memcpy(
        oDataBuffer, 
        (void *) &(((uint8_t *)iSmaBuf->vData)[iSmaBuf->vBufferOffset]), 
        iDataBufferSize);

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fSetTargetBaseAddress(SmaBuf_t * iSmaBuf, uint32_t iTargetBaseAddress)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iTargetBaseAddress > iSmaBuf->vTargetSize - iSmaBuf->vBufferSize)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_TARGET_ADDRESS_TOO_HIGH;
    }

    iSmaBuf->vTargetBaseAddress = iTargetBaseAddress;

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fGetTargetBaseAddress(SmaBuf_t * iSmaBuf, uint32_t * oTargetBaseAddress)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    *oTargetBaseAddress = iSmaBuf->vTargetBaseAddress;

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fSetBufferOffset(SmaBuf_t * iSmaBuf, uint32_t iBufferOffset)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    if(iBufferOffset >= iSmaBuf->vBufferSize)
    {
        PRV__M_TRY_SEM_GIVE(iSmaBuf);
        return SMA_BUF__C_ERROR_BUFFER_OFFSET_TOO_HIGH;
    }

    iSmaBuf->vBufferOffset = iBufferOffset;

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}


SmaBuf_tRetVal SmaBuf_fGetBufferOffset(SmaBuf_t * iSmaBuf, uint32_t * oBufferOffset)
{
    PRV__M_TRY_SEM_TAKE(iSmaBuf);

    *oBufferOffset = iSmaBuf->vBufferOffset;

    PRV__M_TRY_SEM_GIVE(iSmaBuf);

    return SMA_BUF__C_SUCCESS;
}
