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

#include "commands.h"
#include <string.h>

#define PRV__M_CHECK_NULL(iPtr)                                                \
    if(iPtr == NULL)                                                           \
        return CMD__C_ERROR_IS_NULL


static const char * Prv_vRetValStrings[] = {
    [CMD__C_SUCCESS] = "The function ran successfully.",
    [CMD__C_FAIL] = "The function failed.",
    [CMD__C_ERROR_IS_NULL] =  "A null pointer was passed to the function.",
    [CMD__C_ERROR_COMMAND_FAILED] = "The command handler failed.",
    [CMD__C_ERROR_COMMAND_NOT_FOUND] = "The command identifier was not found in the command table."
};


Cmd_tRetVal Cmd_fRunCommandByName(Cmd_tCmdTable * iCmdTable, const char * iCmdName, void * iBuffer, void * oBuffer)
{
    uint32_t vCmdIndex;

    PRV__M_CHECK_NULL(iCmdTable);

    for(vCmdIndex = 0; vCmdIndex < iCmdTable->vNumberOfCommands; vCmdIndex++)
        if(strcmp(iCmdName, iCmdTable->vCommandList[vCmdIndex].vName) == 0)
            break;

    if (vCmdIndex == iCmdTable->vNumberOfCommands)
        return CMD__C_ERROR_COMMAND_NOT_FOUND;

    if (iCmdTable->vCommandList[vCmdIndex].fHandler(iBuffer, oBuffer) != 0)
        return CMD__C_ERROR_COMMAND_FAILED;

    return CMD__C_SUCCESS;
}


Cmd_tRetVal Cmd_fRunCommandByIndex(Cmd_tCmdTable * iCmdTable, uint32_t iCmdIndex, void * iBuffer, void * oBuffer)
{
    PRV__M_CHECK_NULL(iCmdTable);

    if(iCmdIndex >= iCmdTable->vNumberOfCommands)
        return CMD__C_ERROR_COMMAND_NOT_FOUND;

    if (iCmdTable->vCommandList[iCmdIndex].fHandler(iBuffer, oBuffer) != 0)
        return CMD__C_ERROR_COMMAND_FAILED;

    return CMD__C_SUCCESS;
}


const char * Cmd_fGetRetValStr(Cmd_tRetVal iRetVal)
{
    return Prv_vRetValStrings[iRetVal];
}
