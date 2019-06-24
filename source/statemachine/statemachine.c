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

#include "statemachine.h"
#include <string.h>


#define PRV__M_TRY_SEM_TAKE(iStaMacPtr)                                       \
    if(iStaMacPtr->vSemaphoreInterface->fTake(iStaMacPtr->vSemaphore) != 0)   \
        return STA_MAC__C_ERROR_SEMAPHORE_TAKE


#define PRV__M_TRY_SEM_GIVE(iStaMacPtr)                                       \
    if(iStaMacPtr->vSemaphoreInterface->fGive(iStaMacPtr->vSemaphore) != 0)   \
        return STA_MAC__C_ERROR_SEMAPHORE_GIVE


#define PRV__M_CHECK_NULL(iPointer)                                           \
    if(!iPointer)                                                             \
        return STA_MAC__C_ERROR_IS_NULL


StaMac_tRetVal StaMac_fEvent(StaMac_t * iStaMac, const uint8_t * iEvent, void * ioEventArguments)
{
    uint32_t vStateIndex;
    uint32_t vEventIndex;

    PRV__M_TRY_SEM_TAKE(iStaMac);

    for(vStateIndex = 0; vStateIndex < iStaMac->vNumberOfStates; vStateIndex++)
        if(strncmp(iStaMac->vStateTable[vStateIndex].vName, iStaMac->vCurrentState, C_STATE_NAME_LENGTH_MAX) == 0)
            break;

    if (vStateIndex == iStaMac->vNumberOfStates)
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_INVALID_STATE;
    }

    for(vEventIndex = 0; vEventIndex < iStaMac->vStateTable[vStateIndex].vNumberOfTransitions; vEventIndex++)
        if(strncmp(iStaMac->vStateTable[vStateIndex].vTransitions[vEventIndex].vEvent, iEvent, C_EVENT_NAME_LENGTH_MAX) == 0)
            break;

    if (vEventIndex == iStaMac->vStateTable[vStateIndex].vNumberOfTransitions)  
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_INVALID_EVENT;
    }

    if(iStaMac->vStateTable[vStateIndex].vTransitions[vEventIndex].fHandler(ioEventArguments) != 0)
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_TRANSITION_HANDLER;
    }

    strncpy(iStaMac->vCurrentState, iStaMac->vStateTable[vStateIndex].vTransitions[vEventIndex].vTargetState, C_STATE_NAME_LENGTH_MAX);

    PRV__M_TRY_SEM_GIVE(iStaMac);

    return STA_MAC__C_SUCCESS;
}


StaMac_tRetVal StaMac_fRunState(StaMac_t * iStaMac, void * ioStateArguments)
{
    uint32_t vStateIndex;

    PRV__M_TRY_SEM_TAKE(iStaMac);

    for(vStateIndex = 0; vStateIndex < iStaMac->vNumberOfStates; vStateIndex++)
        if(strncmp(iStaMac->vStateTable[vStateIndex].vName, iStaMac->vCurrentState, C_STATE_NAME_LENGTH_MAX) == 0)
            break;

    if (vStateIndex == iStaMac->vNumberOfStates)
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_INVALID_STATE;
    }

    if(iStaMac->vStateTable[vStateIndex].fHandler(ioStateArguments) != 0)
        return STA_MAC__C_ERROR_STATE_HANDLER;

    PRV__M_TRY_SEM_GIVE(iStaMac);

    return STA_MAC__C_SUCCESS;
}


StaMac_tRetVal StaMac_fGetState(StaMac_t * iStaMac, uint8_t * oStateBuffer, uint32_t iStateBufferSize)
{
    uint32_t vStateIndex;
    uint32_t vStateNameLength;

    PRV__M_TRY_SEM_TAKE(iStaMac);

    for(vStateIndex = 0; vStateIndex < iStaMac->vNumberOfStates; vStateIndex++)
        if(strncmp(iStaMac->vStateTable[vStateIndex].vName, iStaMac->vCurrentState, C_STATE_NAME_LENGTH_MAX) == 0)
            break;

    if (vStateIndex == iStaMac->vNumberOfStates)
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_INVALID_STATE;
    }

    vStateNameLength = strlen(iStaMac->vCurrentState);

    if (iStateBufferSize < vStateNameLength)
    {
        PRV__M_TRY_SEM_GIVE(iStaMac);
        return STA_MAC__C_ERROR_STATE_NAME_DOES_NOT_FIT;
    }

    strncpy(oStateBuffer, iStaMac->vCurrentState, vStateNameLength);

    PRV__M_TRY_SEM_GIVE(iStaMac);

    return STA_MAC__C_SUCCESS;
}
