#ifndef _SEM_H_
#define _SEM_H_

#include <stdint.h>

typedef enum Sem_eRetVal
{
    SEM__C_SUCCESS,
    SEM__C_FAIL,
    SEM__C_ERROR_TIMEOUT
} Sem_tRetVal;

typedef uint32_t (*Sem_tCallback)(void *);

typedef struct Sem_sInterruptInterface
{
    Sem_tCallback fDisableInterrupts;
    Sem_tCallback fEnableInterrupts;
    Sem_tCallback fWaitForInterrupt;
} Sem_tInterruptInterface;

typedef struct Sem_sTimerInterface
{
    Sem_tCallback fStart;
    Sem_tCallback fStop;
    Sem_tCallback fReload;
    Sem_tCallback fIsExpired;
} Sem_tTimerInterface;

typedef struct Sem_s
{
    volatile int32_t vValue;
    void * vTimer;
    const Sem_tInterruptInterface * vInterruptInterface;
    const Sem_tTimerInterface * vTimerInterface;
} Sem_t;


Sem_tRetVal Sem_fTake(Sem_t * iSem);
Sem_tRetVal Sem_fGive(Sem_t * iSem);

#endif
