#include "counter/counter.h"


Cou_tRetVal Cou_fReset(Cou_t * iCounter)
{
    iCounter->vCount = 0;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fStart(Cou_t * iCounter)
{
    iCounter->vCounting = true;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fStop(Cou_t * iCounter)
{
    iCounter->vCounting = false;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIncrement(Cou_t * iCounter)
{
    bool vIsCounting;
    bool vIsExpired;
    
    Cou_fIsCounting(iCounter, &vIsCounting);
    Cou_fIsExpired(iCounter, &vIsExpired);

    if(!vIsCounting)
        return COU__C_ERROR_NOT_COUNTING;

    if(vIsExpired)
        return COU__C_ERROR_IS_EXPIRED;

    iCounter->vCount++;

    Cou_fIsExpired(iCounter, &vIsExpired);

    if(vIsExpired)
        iCounter->fExpiryNotificationCallback(iCounter->vExpiryNotificationArguments);

    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fSetTargetValue(Cou_t * iCounter, uint32_t iTargetValue)
{
    iCounter->vTargetValue = iTargetValue;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fGetCount(Cou_t * iCounter, uint32_t * oCount)
{
    *oCount = iCounter->vCount;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIsCounting(Cou_t * iCounter, bool * oIsCounting)
{
    *oIsCounting = iCounter->vCounting;
    return COU__C_SUCCESS;
}


Cou_tRetVal Cou_fIsExpired(Cou_t * iCounter, bool * oIsExpired)
{
    *oIsExpired = iCounter->vCount >= iCounter->vTargetValue;
    return COU__C_SUCCESS;
}

