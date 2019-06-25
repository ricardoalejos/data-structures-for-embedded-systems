#include "commands/commands.h"
#include <stdio.h>
#include <ctype.h>

uint32_t fToUpperCommandHandler(void * i, void * o)
{
    *((char *)o) = (char) toupper(*((char *)i));
    printf("%c -> To Upper -> %c.\n", *((char *)i), *((char *)o));
    return 0;
}

uint32_t fToLowerCommandHandler(void * i, void * o)
{
    *((char *)o) = (char) tolower(*((char *)i));
    printf("%c -> To Lower -> %c.\n", *((char *)i), *((char *)o));
    return 0;
}

uint32_t fFailOnPurposeCommandHandler(void * i, void * o)
{
    printf("Failing on purpose... Woops!\n");
    return 1;
}

Cmd_tCmdTable ExampleCmdTable = {
    .vNumberOfCommands = 3,
    .vCommandList = (Cmd_t []){
        {.vName = "TO_UPPER", .fHandler = fToUpperCommandHandler},
        {.vName = "TO_LOWER", .fHandler = fToLowerCommandHandler},
        {.vName = "FAIL_ON_PURPOSE", .fHandler = fFailOnPurposeCommandHandler},
    }
};


int main()
{
    char vTestInput[] = "x";
    char vTestOutput[sizeof(vTestInput)];
    printf("%s\n\n", Cmd_fGetRetValStr(Cmd_fRunCommandByName(&ExampleCmdTable, "TO_UPPER", vTestInput, vTestOutput)));
    printf("%s\n\n", Cmd_fGetRetValStr(Cmd_fRunCommandByName(&ExampleCmdTable, "TO_LOWER", vTestInput, vTestOutput)));
    printf("%s\n\n", Cmd_fGetRetValStr(Cmd_fRunCommandByName(&ExampleCmdTable, "FAIL_ON_PURPOSE", vTestInput, vTestOutput)));
    printf("%s\n\n", Cmd_fGetRetValStr(Cmd_fRunCommandByIndex(&ExampleCmdTable, 2, vTestInput, vTestOutput)));
    printf("%s\n\n", Cmd_fGetRetValStr(Cmd_fRunCommandByName(&ExampleCmdTable, "DO_MAGIC", vTestInput, vTestOutput)));

    return 0;
}
