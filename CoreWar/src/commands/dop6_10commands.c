/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop6-10commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 07:01:00 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:19:34 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void			dop_and_function(t_data_prog *data_prog, unsigned int *result,
						unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
			+ data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a & b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

void			dop_or_function(t_data_prog *data_prog, unsigned int *result,
								unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
										+ data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a | b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

void			dop_xor_function(t_data_prog *data_prog, unsigned int *result,
								unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
												data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a ^ b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

unsigned int	dop_load_index_function(t_data_prog *data_prog,
						unsigned int result, unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[1] = (short)data_prog->pc->options->dir[1];
		b = data_prog->pc->options->dir[1];
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] =
			bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
					(short)((short)(a + b) % IDX_MOD));
	return (result);
}
