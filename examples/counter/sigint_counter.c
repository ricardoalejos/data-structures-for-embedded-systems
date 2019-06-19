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

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include "counter/counter.h"


uint32_t fExampleExpiryNotification(void * args);

Cou_t vExampleCounter = {
    .vTargetValue = 3,
    .vCount = 0,
    .vCounting = false,
    .fExpiryNotificationCallback = fExampleExpiryNotification,
    .vExpiryNotificationArguments = NULL
};


void sig_handler(int signo)
{
    uint32_t vExampleCounterValue;
    Cou_tRetVal vRetVal;

    if (signo == SIGINT)
    {
        vRetVal = Cou_fIncrement(&vExampleCounter);
        if(vRetVal != COU__C_SUCCESS)
            printf("The Example Counter cannot be incremented (err=%d).\n", (int)vRetVal);

        vRetVal = Cou_fGetCount(&vExampleCounter, &vExampleCounterValue);
        if(vRetVal == COU__C_SUCCESS)
            printf(
                "Received a SIGINT event. "
                "The Example Counter value is %d.\n",
                vExampleCounterValue);
        else
            printf("Cannot check the Example Counter value.\n");
    }

}

uint32_t fExampleExpiryNotification(void * args)
{
    printf("The example counter has reached its target value.\n");
    Cou_fReset(&vExampleCounter);
    return 0;
}


int main(void)
{
    pid_t vMyPid;

    vMyPid = getpid();

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    Cou_fStart(&vExampleCounter);

    printf("Running the 'counter_example' application (PID=%d).\n", vMyPid);
    printf("Send a SIGINT signal to increment the counter, or SIGKILL to quit.\n");

    while(1) 
        sleep(1);
        
    
    return 0;
}