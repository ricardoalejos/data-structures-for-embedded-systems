
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