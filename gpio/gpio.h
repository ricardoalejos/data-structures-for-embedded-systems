
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
Gpio_tRetVal Gpio_fNotifyInterrupt(Gpio_t * iGpio);

#endif
