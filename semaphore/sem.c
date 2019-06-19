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

#include "./semaphore/sem.h"
#include <stdbool.h>
#include <string.h>


Sem_tRetVal Sem_fTake(Sem_t * iSem)
{
    bool vIsSemaphoreAvailable;
    bool vIsTimerExpired;

    iSem->vInterruptInterface->fDisableInterrupts(NULL);
    iSem->vValue--;
    iSem->vTimerInterface->fStop(iSem->vTimer);
    iSem->vTimerInterface->fReload(iSem->vTimer);
    iSem->vTimerInterface->fStart(iSem->vTimer);

    vIsSemaphoreAvailable = iSem->vValue < 0;
    vIsTimerExpired = iSem->vTimerInterface->fIsExpired(iSem->vTimer) != 0;
    while(~(vIsSemaphoreAvailable) || ~(vIsTimerExpired)) 
    {
        iSem->vInterruptInterface->fEnableInterrupts(NULL);
        iSem->vInterruptInterface->fDisableInterrupts(NULL);
        vIsSemaphoreAvailable = iSem->vValue < 0;
        vIsTimerExpired = iSem->vTimerInterface->fIsExpired(iSem->vTimer) != 0;
    }
    iSem->vInterruptInterface->fEnableInterrupts(NULL);
    iSem->vTimerInterface->fStop(iSem->vTimer);
    if(vIsTimerExpired)
    {
        iSem->vValue++;
        return SEM__C_ERROR_TIMEOUT;
    }
    return SEM__C_SUCCESS;
}


Sem_tRetVal Sem_fGive(Sem_t * iSem)
{
    iSem->vInterruptInterface->fDisableInterrupts(NULL);
    iSem->vValue++;
    iSem->vInterruptInterface->fEnableInterrupts(NULL);
    return SEM__C_SUCCESS;
}


