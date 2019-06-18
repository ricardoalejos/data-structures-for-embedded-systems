
#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum Cou_eRetVal
{
    COU__C_SUCCESS,
    COU__C_FAIL,
    COU__C_ERROR_NOT_COUNTING,
    COU__C_ERROR_IS_EXPIRED
} Cou_tRetVal;

typedef uint32_t (*Cou_tCallback)(void *);

typedef struct Cou_s
{
    uint32_t vTargetValue;
    volatile uint32_t vCount;
    volatile bool vCounting;
    Cou_tCallback fExpiryNotificationCallback;
    void * vExpiryNotificationArguments;
} Cou_t;


Cou_tRetVal Cou_fReset(Cou_t * iCounter);
Cou_tRetVal Cou_fStart(Cou_t * iCounter);
Cou_tRetVal Cou_fStop(Cou_t * iCounter);
Cou_tRetVal Cou_fIncrement(Cou_t * iCounter);
Cou_tRetVal Cou_fSetTargetValue(Cou_t * iCounter, uint32_t iTargetValue);
Cou_tRetVal Cou_fGetCount(Cou_t * iCounter, uint32_t * oCount);
Cou_tRetVal Cou_fIsExpired(Cou_t * iCounter, bool * oIsExpired);
Cou_tRetVal Cou_fIsCounting(Cou_t * iCounter, bool * oIsCounting);

#endif