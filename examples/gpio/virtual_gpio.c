#include "virtual_gpio.h"
#include <stdio.h>
#include <string.h>

uint32_t fVirtualSetAsInput(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;

    printf("port[%d].pin[%d].direction <- INPUT.\n", vPin, vPort);

    return 0;
}


uint32_t fVirtualSetAsOutput(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;

    printf("port[%d].pin[%d].direction <- OUTPUT.\n", vPin, vPort);

    return 0;
}


uint32_t fVirtualSetDataLow(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;
    ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vData = 0;

    printf("port[%d].pin[%d].data <- LOW.\n", vPin, vPort);

    return 0;
}


uint32_t fVirtualSetDataHigh(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;
    ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vData = 1;

    printf("port[%d].pin[%d].data <- HIGH.\n", vPin, vPort);

    return 0;
}


uint32_t fVirtualReadData(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    uint32_t vData;
    
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;
    vData = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vData;

    if(vData == 0) 
    {
        printf("port[%d].pin[%d].data -> LOW.\n", vPin, vPort);
        iGpio->vDataValue = GPIO__C_LOW;
    }
    else
    {
        printf("port[%d].pin[%d].data -> HIGH.\n", vPin, vPort);
        iGpio->vDataValue = GPIO__C_HIGH;
    }
    return 0;
}

uint32_t fVirtualInterruptEnable(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    uint32_t vInterruptEnable;
    char vInterruptType[32];

    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;

    switch(iGpio->vInterruptType)
    {
        case GPIO__C_FALLING_EDGE:
            vInterruptEnable = 1;
            strncpy(vInterruptType, "FALLING_EDGE", 32);
            break;
        case GPIO__C_RISING_EDGE:
            vInterruptEnable = 1;
            strncpy(vInterruptType, "RISING_EDGE", 32);
            break;
        case GPIO__C_TOGGLE:
            vInterruptEnable = 1;
            strncpy(vInterruptType, "TOGGLE", 32);
            break;
        default:
            vInterruptEnable = 0;
            strncpy(vInterruptType, "NONE", 32);
            break;
    }

    ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptEnable = vInterruptEnable;
    strncpy(((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptType, vInterruptType, 32);
    printf("port[%d].pin[%d].interrupt_enable <- %d.\n", vPin, vPort, vInterruptEnable);
    printf("port[%d].pin[%d].interrupt_type <- %s.\n", vPin, vPort, vInterruptType);

    return 0;
}

uint32_t fVirtualInterruptDisable(Gpio_t * iGpio)
{
    uint32_t vPort;
    uint32_t vPin;
    uint32_t vInterruptEnable;
    char vInterruptType[32];

    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;
    vInterruptEnable = 0;
    strncpy(vInterruptType, "NONE", 32);

    ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptEnable = vInterruptEnable;
    strncpy(((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptType, vInterruptType, 32);
    printf("port[%d].pin[%d].interrupt_enable <- %d.\n", vPin, vPort, vInterruptEnable);
    printf("port[%d].pin[%d].interrupt_type <- %s.\n", vPin, vPort, vInterruptType);

    return 0;
}


uint32_t fVirtualInterruptNotification(Gpio_t * iGpio)
{
    uint32_t vPin;
    uint32_t vPort;
    char * vInterruptType;

    vPin = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPin;
    vPort = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vPort;
    vInterruptType = ((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptType;

    if(((tVirtualGpioDetails *) iGpio->vImplementationDetails)->vInterruptEnable == 1)
    {
        printf("Interrupt of type %s in port[%d].pin[%d].\n", vInterruptType, vPin, vPort);
        Gpio_fNotifyInterrupt(iGpio);
    }
    
}
