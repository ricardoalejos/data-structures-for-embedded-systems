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

#include "counter/counter.h"


Cou_tRetVal Cou_fReset(Cou_t * iCounter)
{
    iCounter->vCount = 0;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fStart(Cou_t * iCounter)
{
    iCounter->vCounting = true;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fStop(Cou_t * iCounter)
{
    iCounter->vCounting = false;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIncrement(Cou_t * iCounter)
{
    bool vIsCounting;
    bool vIsExpired;
    
    Cou_fIsCounting(iCounter, &vIsCounting);
    Cou_fIsExpired(iCounter, &vIsExpired);

    if(!vIsCounting)
        return COU__C_ERROR_NOT_COUNTING;

    if(vIsExpired)
        return COU__C_ERROR_IS_EXPIRED;

    iCounter->vCount++;

    Cou_fIsExpired(iCounter, &vIsExpired);

    if(vIsExpired)
        iCounter->fExpiryNotificationCallback(iCounter->vExpiryNotificationArguments);

    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fSetTargetValue(Cou_t * iCounter, uint32_t iTargetValue)
{
    iCounter->vTargetValue = iTargetValue;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fGetCount(Cou_t * iCounter, uint32_t * oCount)
{
    *oCount = iCounter->vCount;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIsCounting(Cou_t * iCounter, bool * oIsCounting)
{
    *oIsCounting = iCounter->vCounting;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIsExpired(Cou_t * iCounter, bool * oIsExpired)
{
    *oIsExpired = iCounter->vCount >= iCounter->vTargetValue;
    return COU__C_SUCCESS;
}

