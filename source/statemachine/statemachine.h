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

#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_


#include <stdint.h>

#define C_STATE_NAME_LENGTH_MAX         32
#define C_EVENT_NAME_LENGTH_MAX         32

typedef enum StaMac_eRetVal
{
    STA_MAC__C_SUCCESS,
    STA_MAC__C_FAIL,
    STA_MAC__C_ERROR_INVALID_STATE,
    STA_MAC__C_ERROR_INVALID_EVENT,
    STA_MAC__C_ERROR_TRANSITION_HANDLER,
    STA_MAC__C_ERROR_STATE_HANDLER,
    STA_MAC__C_ERROR_STATE_NAME_DOES_NOT_FIT,
    STA_MAC__C_ERROR_SEMAPHORE_TAKE,
    STA_MAC__C_ERROR_SEMAPHORE_GIVE,
    STA_MAC__C_ERROR_IS_NULL
} StaMac_tRetVal;

typedef uint32_t (* StaMac_tCallback)(void * ioArguments);

typedef struct StaMac_sSemaphoreInterface
{
    StaMac_tCallback fTake;
    StaMac_tCallback fGive;
} StaMac_tSemaphoreInterface;

typedef struct StaMac_sTransition
{
    const uint8_t * const vEvent;
    const uint8_t * const vTargetState;
    StaMac_tCallback fHandler; 
} StaMac_tTransition;

typedef struct StaMac_sState
{
    const uint8_t * const vName;
    StaMac_tCallback fHandler;
    const uint32_t vNumberOfTransitions;
    const StaMac_tTransition *  vTransitions;
} StaMac_tState;

typedef struct StaMac_s
{
    const uint32_t vNumberOfStates;
    const StaMac_tState * vStateTable;  
    uint8_t vCurrentState[C_STATE_NAME_LENGTH_MAX];
    void * vSemaphore;
    StaMac_tSemaphoreInterface * vSemaphoreInterface;
} StaMac_t;

StaMac_tRetVal StaMac_fEvent(StaMac_t * iStaMac, const uint8_t * iEvent, void * ioEventArguments);
StaMac_tRetVal StaMac_fRunState(StaMac_t * iStaMac, void * ioStateArguments);
StaMac_tRetVal StaMac_fGetState(StaMac_t * iStaMac, uint8_t * oStateBuffer, uint32_t iStateBufferSize);


#endif