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

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdint.h>

typedef uint32_t (*Cmd_tCallback)(void * iBuffer, void * oBuffer);

typedef struct Cmd_s
{
    const char * const vName;
    const Cmd_tCallback fHandler;
} Cmd_t;

typedef enum Cmd_eRetVal
{
    CMD__C_SUCCESS,
    CMD__C_FAIL,
    CMD__C_ERROR_COMMAND_NOT_FOUND,
    CMD__C_ERROR_IS_NULL,
    CMD__C_ERROR_COMMAND_FAILED
} Cmd_tRetVal;

typedef struct Cmd_sCmdTable
{
    const uint32_t vNumberOfCommands;
    Cmd_t * vCommandList;
} Cmd_tCmdTable;

Cmd_tRetVal Cmd_fRunCommandByName(Cmd_tCmdTable * iCmdTable, const char * iCmdName, void * iBuffer, void * oBuffer);
Cmd_tRetVal Cmd_fRunCommandByIndex(Cmd_tCmdTable * iCmdTable, uint32_t iCmdIndex, void * iBuffer, void * oBuffer);
const char * Cmd_fGetRetValStr(Cmd_tRetVal iRetVal);

#endif