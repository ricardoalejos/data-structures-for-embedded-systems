#include "./semaphore/sem.h"
#include <stdbool.h>
#include <string.h>


Sem_tRetVal Sem_fTake(Sem_t * iSem)
{
    bool vIsSemaphoreAvailable;
    bool vIsTimerExpired;

    iSem->vInterruptInterface->fDisableInterrupts(NULL);
    iSem->vValue--;
    iSem->vTimerInterface->fStop(iSem->vTimer);
    iSem->vTimerInterface->fReload(iSem->vTimer);
    iSem->vTimerInterface->fStart(iSem->vTimer);

    vIsSemaphoreAvailable = iSem->vValue < 0;
    vIsTimerExpired = iSem->vTimerInterface->fIsExpired(iSem->vTimer) != 0;
    while(~(vIsSemaphoreAvailable) || ~(vIsTimerExpired)) 
    {
        iSem->vInterruptInterface->fEnableInterrupts(NULL);
        iSem->vInterruptInterface->fDisableInterrupts(NULL);
        vIsSemaphoreAvailable = iSem->vValue < 0;
        vIsTimerExpired = iSem->vTimerInterface->fIsExpired(iSem->vTimer) != 0;
    }
    iSem->vInterruptInterface->fEnableInterrupts(NULL);
    iSem->vTimerInterface->fStop(iSem->vTimer);
    if(vIsTimerExpired)
    {
        iSem->vValue++;
        return SEM__C_ERROR_TIMEOUT;
    }
    return SEM__C_SUCCESS;
}


Sem_tRetVal Sem_fGive(Sem_t * iSem)
{
    iSem->vInterruptInterface->fDisableInterrupts(NULL);
    iSem->vValue++;
    iSem->vInterruptInterface->fEnableInterrupts(NULL);
    return SEM__C_SUCCESS;
}


