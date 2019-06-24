#include "statemachine/statemachine.h"
#include <stdint.h>
#include <stdio.h>


typedef struct sEventArguments {
        StaMac_t * vStateMachine;
        uint8_t * vEventName;
} tEventArguments;

uint32_t fSemaphoreCallbackDummy(void * iSemaphore);
uint32_t fGenericStateHandler(void * ioArguments);
uint32_t fGenericTransitionHandler(void * ioArguments);

StaMac_t ExampleStateMachine = {
    .vSemaphoreInterface = (StaMac_tSemaphoreInterface []) {{
        .fTake = fSemaphoreCallbackDummy,
        .fGive = fSemaphoreCallbackDummy
    }},
    .vSemaphore = (void *) 0,
    .vNumberOfStates = 2,
    .vCurrentState = "StateA",
    .vStateTable = (StaMac_tState []) {
        {
            .vName = "StateA",
            .fHandler = fGenericStateHandler,
            .vNumberOfTransitions = 2,
            .vTransitions = (StaMac_tTransition []){
                {
                    .vEvent = "EventX",
                    .fHandler = fGenericTransitionHandler,
                    .vTargetState = "StateB"
                },
                {
                    .vEvent = "EventY",
                    .fHandler = fGenericTransitionHandler,
                    .vTargetState = "StateA"
                }
            }
        },
        {
            .vName = "StateB",
            .fHandler = fGenericStateHandler,
            .vNumberOfTransitions = 2,
            .vTransitions = (StaMac_tTransition []){
                {
                    .vEvent = "EventX",
                    .fHandler = fGenericTransitionHandler,
                    .vTargetState = "StateA"
                },
                {
                    .vEvent = "EventY",
                    .fHandler = fGenericTransitionHandler,
                    .vTargetState = "StateB"
                }
            }
        }
    }
};


uint32_t fSemaphoreCallbackDummy(void * iSemaphore)
{
    return 0;
}


uint32_t fGenericStateHandler(void * ioArguments)
{
    printf("State handler of state: %s.\n",
        ((StaMac_t *) ioArguments)->vCurrentState
    );

    return 0;
}


uint32_t fGenericTransitionHandler(void * ioArguments)
{
    tEventArguments * vArgumentsPointer = ioArguments;
    printf("Transition handler of state: %s. (event '%s').\n",
        vArgumentsPointer->vStateMachine->vCurrentState,
        vArgumentsPointer->vEventName);

    return 0;    
}


uint32_t main()
{
    tEventArguments vEventArguments = {
        .vStateMachine = &ExampleStateMachine,
        .vEventName = "EventX"
    };

    StaMac_tRetVal vRetVal;

    // Run the state handler of the initial state (StateA).
    vRetVal = StaMac_fRunState(&ExampleStateMachine, &ExampleStateMachine);

    // Signal EventX, and the state machine goes to StateB.
    vRetVal = StaMac_fEvent(&ExampleStateMachine, "EventX", &vEventArguments);
    vRetVal = StaMac_fRunState(&ExampleStateMachine, &ExampleStateMachine);

    // Signal EventX, and the state machine goes back to StateA.
    vRetVal = StaMac_fEvent(&ExampleStateMachine, "EventX", &vEventArguments);
    vRetVal = StaMac_fRunState(&ExampleStateMachine, &ExampleStateMachine);

    // Signal EventY, the state machine should keep itself in StateA.
    vEventArguments.vEventName = "EventY";
    vRetVal = StaMac_fEvent(&ExampleStateMachine, "EventY", &vEventArguments);
    vRetVal = StaMac_fRunState(&ExampleStateMachine, &ExampleStateMachine);

    return vRetVal;
}