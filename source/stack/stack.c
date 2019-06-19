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

#include "stack.h"
#include "stddef.h"
#include "string.h"


stack_ret_t stack_is_full(stack_t * stack, bool * response)
{
	if(stack == NULL)
		return STACK_FAIL;

	if(stack->stack_size >= stack->stack_capacity)
		*response = true;
	else
		*response = false;

	return STACK_SUCCESS;
}


stack_ret_t stack_is_empty(stack_t * stack, bool * response)
{
	if(stack == NULL)
		return STACK_FAIL;

	if(stack->stack_size == 0)
		*response = true;
	else
		*response = false;

	return STACK_SUCCESS;
}


stack_ret_t stack_push(stack_t * stack, void * item_buffer, size_t item_size)
{
	bool is_full;
	void * memcpy_return_value;

	if(stack_is_full(stack, &is_full) == STACK_FAIL)
		return STACK_FAIL;

	if(stack->element_size < item_size || is_full)
		return STACK_FAIL;

	memcpy_return_value = memcpy(
			(void *) &stack->buffer[stack->stack_size * stack->element_size],
			item_buffer,
			item_size);

	if (memcpy_return_value == NULL)
		return STACK_FAIL;

	stack->stack_size++;

	return STACK_SUCCESS;
}


stack_ret_t stack_pop(stack_t * stack, void * item_buffer, size_t item_size)
{
	bool is_empty;
	void * memcpy_return_value;
	void * memset_return_value;

	if(stack_is_empty(stack, &is_empty) == STACK_FAIL)
		return STACK_FAIL;

	if(is_empty || item_size > stack->element_size)
		return STACK_FAIL;

	memcpy_return_value = memcpy(
			item_buffer,
			(void *) &stack->buffer[(stack->stack_size - 1) * stack->element_size],
			item_size);

	if (memcpy_return_value == NULL)
		return STACK_FAIL;

	memset_return_value = memset(
			(void *) &stack->buffer[(stack->stack_size - 1) * stack->element_size],
			0,
			stack->element_size);

	if (memset_return_value == NULL)
		return STACK_FAIL;

	stack->stack_size--;

	return STACK_SUCCESS;
}


stack_ret_t stack_clear(stack_t * stack)
{
	void * memset_return_value;

	if(stack == NULL)
		return STACK_FAIL;

	memset_return_value = memset(
			(void *) stack->buffer,
			0,
			stack->element_size * stack->stack_capacity);

	stack->stack_size = 0;

	if (memset_return_value == NULL)
		return STACK_FAIL;

	return STACK_SUCCESS;
}


