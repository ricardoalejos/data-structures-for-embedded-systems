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

#include "gpio/gpio.h"


Gpio_tRetVal Gpio_fSetAsInput(Gpio_t * iGpio)
{
    uint32_t vIfcRetVal;

    vIfcRetVal = iGpio->vImplementationInterface->fSetAsInput(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    iGpio->vDirection = GPIO__C_INPUT;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fSetAsOutput(Gpio_t * iGpio)
{
    uint32_t vIfcRetVal;

    vIfcRetVal = iGpio->vImplementationInterface->fSetAsOutput(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    iGpio->vDirection = GPIO__C_OUTPUT;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fSetDataHigh(Gpio_t * iGpio)
{
    uint32_t vIfcRetVal;

    vIfcRetVal = iGpio->vImplementationInterface->fSetDataHigh(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    iGpio->vDataValue = GPIO__C_HIGH;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fSetDataLow(Gpio_t * iGpio)
{
    uint32_t vIfcRetVal;

    vIfcRetVal = iGpio->vImplementationInterface->fSetDataLow(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    iGpio->vDataValue = GPIO__C_LOW;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fReadData(Gpio_t * iGpio, Gpio_tDataValue * oValue)
{
    uint32_t vIfcRetVal;

    vIfcRetVal = iGpio->vImplementationInterface->fReadData(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    *oValue = iGpio->vDataValue;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fToggleData(Gpio_t * iGpio)
{
    uint32_t vIfcRetVal;
    Gpio_tDataValue vOldValue;

    vIfcRetVal = Gpio_fReadData(iGpio, &vOldValue);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;
    
    if(vOldValue == GPIO__C_LOW)
        vIfcRetVal = Gpio_fSetDataHigh(iGpio);
    else
        vIfcRetVal = Gpio_fSetDataLow(iGpio);

    if (vIfcRetVal != 0)
        return GPIO__C_FAIL;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fInterruptEnable(Gpio_t * iGpio)
{
    uint32_t vIntRetVal;

    vIntRetVal = iGpio->vImplementationInterface->fInterruptEnable(iGpio);

    if (vIntRetVal != 0)
        return GPIO__C_FAIL;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fInterruptDisable(Gpio_t * iGpio)
{
    uint32_t vIntRetVal;

    vIntRetVal = iGpio->vImplementationInterface->fInterruptDisable(iGpio);

    if (vIntRetVal != 0)
        return GPIO__C_FAIL;

    return GPIO__C_SUCCESS;
}


Gpio_tRetVal Gpio_fNotifyInterrupt(Gpio_t * iGpio)
{
    uint32_t vIntRetVal;

    vIntRetVal = iGpio->fInterruptNotification(iGpio);

    if (vIntRetVal != 0)
        return GPIO__C_FAIL;

    return GPIO__C_SUCCESS;
}
