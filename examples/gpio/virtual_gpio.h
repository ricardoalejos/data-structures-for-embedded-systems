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

#ifndef _VIRTUAL_GPIO_H_
#define _VIRTUAL_GPIO_H_

#include "gpio/gpio.h"
#include <stdint.h>

typedef struct sVirtualGpioDetails
{
    uint32_t vPort;
    uint32_t vPin;
    uint32_t vData;
    uint32_t vInterruptEnable;
    char vInterruptType[32];
} tVirtualGpioDetails;

uint32_t fVirtualSetAsInput(Gpio_t * iGpio);
uint32_t fVirtualSetAsOutput(Gpio_t * iGpio);
uint32_t fVirtualSetDataLow(Gpio_t * iGpio);
uint32_t fVirtualSetDataHigh(Gpio_t * iGpio);
uint32_t fVirtualReadData(Gpio_t * iGpio);
uint32_t fVirtualInterruptEnable(Gpio_t * iGpio);
uint32_t fVirtualInterruptDisable(Gpio_t * iGpio);
uint32_t fVirtualInterruptNotification(Gpio_t * iGpio);
uint32_t fExampleInterruptHandler(Gpio_t * iGpio);

#endif