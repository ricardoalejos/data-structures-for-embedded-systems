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

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

typedef enum Gpio_eRetVal
{
    GPIO__C_SUCCESS,
    GPIO__C_FAIL
} Gpio_tRetVal;

typedef enum Gpio_eDirection
{
    GPIO__C_OUTPUT,
    GPIO__C_INPUT
} Gpio_tDirection;

typedef enum Gpio_eDataValue
{
    GPIO__C_LOW,
    GPIO__C_HIGH
} Gpio_tDataValue;

typedef enum Gpio_eInterruptType
{
    GPIO__C_NONE,
    GPIO__C_RISING_EDGE,
    GPIO__C_FALLING_EDGE,
    GPIO__C_TOGGLE
} Gpio_tInterruptType;

struct Gpio_s;

typedef uint32_t (*Gpio_tCallback)(struct Gpio_s * iGpio);

typedef struct Gpio_sGpioInterface
{
    Gpio_tCallback fSetAsInput;
    Gpio_tCallback fSetAsOutput;
    Gpio_tCallback fSetDataHigh;
    Gpio_tCallback fSetDataLow;
    Gpio_tCallback fReadData;
    Gpio_tCallback fInterruptEnable;
    Gpio_tCallback fInterruptDisable;
} Gpio_tGpioInterface;

typedef struct Gpio_s
{
    Gpio_tDirection vDirection;
    Gpio_tDataValue vDataValue;
    Gpio_tInterruptType vInterruptType;
    Gpio_tCallback fInterruptNotification;
    const Gpio_tGpioInterface * vImplementationInterface;
    void * vImplementationDetails;
} Gpio_t;

Gpio_tRetVal Gpio_fSetAsInput(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fSetAsOutput(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fSetDataHigh(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fSetDataLow(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fReadData(Gpio_t * iGpio, Gpio_tDataValue * oValue);
Gpio_tRetVal Gpio_fToggleData(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fInterruptEnable(Gpio_t * iGpio);
Gpio_tRetVal Gpio_fInterruptDisable(Gpio_t * iGpio);

/*  Name
        Gpio_fNotifyInterrupt
    Description
            This function forwards the interrupt notification to the
        Gpio.vInterruptNotification callback. Call this function within
        the ISR that corresponds to the interruption of the passed GPIO.
            Warning: All the structure members that are pointers must be
        initialized. Otherwise, this function could de-reference a null
        pointer.
    Arguments
        Gpio_t * iGpio
                Pointer to the GPIO instance that corresponds to the ISR in
            which this function is invoked.
    Return value
        GPIO__C_FAIL
                The Gpio.vInterruptNotification callback returned a value 
            different than zero (assuming it ran into an error or
            unexpected behavior).
        GPIO__C_SUCCESS
                The Gpio.vInterruptNotification callback returned zero. It
            is assumed that it ran correctly and successfully.
*/
Gpio_tRetVal Gpio_fNotifyInterrupt(Gpio_t * iGpio);

#endif
