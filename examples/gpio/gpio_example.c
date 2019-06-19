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
#include "virtual_gpio.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

const Gpio_tGpioInterface vVirtualGpioInterface = {
    .fSetAsInput = fVirtualSetAsInput,
    .fSetAsOutput = fVirtualSetAsOutput,
    .fSetDataHigh = fVirtualSetDataHigh,
    .fSetDataLow = fVirtualSetDataLow,
    .fReadData = fVirtualReadData,
    .fInterruptEnable = fVirtualInterruptEnable,
    .fInterruptDisable = fVirtualInterruptDisable
};

tVirtualGpioDetails vExampleVirtualGpio = {
    .vPin = 1,
    .vPort = 2,
    .vData = 0,
    .vInterruptEnable = 0,
    .vInterruptType = "NONE"
};

Gpio_t vGpioExample = {
    .vDirection = GPIO__C_OUTPUT,
    .vDataValue = GPIO__C_LOW,
    .vInterruptType = GPIO__C_FALLING_EDGE,
    .fInterruptNotification = fExampleInterruptHandler,
    .vImplementationInterface = &vVirtualGpioInterface,
    .vImplementationDetails = (void *) &vExampleVirtualGpio
};


uint32_t fExampleInterruptHandler(Gpio_t * iGpio)
{
    printf("Interrupt handler: set as output, set value high, and set as input.\n");
    Gpio_fSetAsOutput(&vGpioExample);
    Gpio_fSetDataHigh(&vGpioExample);
    Gpio_fSetAsInput(&vGpioExample);
    return 0;
}


void fSignalHandler(int iSignalId)
{
    if(iSignalId == SIGINT)
    {
        // Falling edge makes vData to be 0
        vExampleVirtualGpio.vData = 0;
        fVirtualInterruptNotification(&vGpioExample);
    }
}


int main()
{
    Gpio_tDataValue vReadData;
    pid_t vMyPid;

    vMyPid = getpid();

    if (signal(SIGINT, fSignalHandler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    Gpio_fSetAsOutput(&vGpioExample);
    Gpio_fSetDataHigh(&vGpioExample);
    Gpio_fSetAsInput(&vGpioExample);
    Gpio_fReadData(&vGpioExample, &vReadData);
    Gpio_fInterruptEnable(&vGpioExample);

    printf("Running the 'gpio_example' application (PID=%d).\n", vMyPid);
    printf("Send a SIGINT signal to inject a GPIO interruption, or SIGKILL to quit.\n");

    while(1)
        sleep(1);

    return 0;
}
