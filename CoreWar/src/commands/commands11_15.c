/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands11-15.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:55:01 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:17:44 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

unsigned int	store_index_function(t_data_prog *data_prog)
{
	unsigned int b;
	unsigned int result;

	result = 3;
	if (data_prog->pc->options->option_number[1] == 1)
	{
		result++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[1] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[1] = (short)data_prog->pc->options->dir[1];
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[1] == 3)
	{
		result += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
				(short)(data_prog->pc->options->ind[1] % IDX_MOD));
	}
	else
		return (1);
	return (dop_store_index_function(data_prog, result, b));
}

unsigned int	fork_function(t_data_prog *data_prog)
{
	t_pc *new_pc;

	new_pc = init_pc();
	nulling_pc(new_pc, true_value_pc_index(data_prog->pc->pc_index +
	(short)((short)data_prog->pc->options->dir[0] % IDX_MOD)));
	new_pc->alive_label = data_prog->pc->alive_label;
	new_pc->action = 0;
	new_pc->pc_number = ++data_prog->pc_number;
	new_pc->carry = data_prog->pc->carry;
	copy_registry(new_pc, data_prog->pc);
	new_pc->next = data_prog->first_pc;
	data_prog->first_pc = new_pc;
	return (3);
}

unsigned int	long_load_command(t_data_prog *data_prog)
{
	unsigned int	result;

	result = 1;
	if (data_prog->pc->options->option_number[0] == 2)
	{
		result = 7;
		data_prog->pc->registry[data_prog->pc->options->reg[1] - 1] =
				data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		result = 5;
		data_prog->pc->registry[data_prog->pc->options->reg[1] - 1] =
				bytestoui(data_prog->game_info->field,
				data_prog->pc->pc_index + data_prog->pc->options->ind[0]);
	}
	if (data_prog->pc->registry[data_prog->pc->options->reg[1] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
	return (result);
}

unsigned int	long_load_index_function(t_data_prog *data_prog)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	result;

	a = 0;
	b = 0;
	result = 3;
	if (data_prog->pc->options->option_number[0] == 1)
	{
		result++;
		a = data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[0] = (short)data_prog->pc->options->dir[0];
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		result += 2;
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
							(short)(data_prog->pc->options->ind[0] % IDX_MOD));
	}
	return (dop_long_load_index_function(data_prog, result, a, b));
}

unsigned int	long_fork_function(t_data_prog *data_prog)
{
	t_pc *new_pc;

	new_pc = init_pc();
	nulling_pc(new_pc, true_value_pc_index(data_prog->pc->pc_index +
	(short)data_prog->pc->options->dir[0]));
	new_pc->alive_label = data_prog->pc->alive_label;
	new_pc->carry = data_prog->pc->carry;
	new_pc->action = 0;
	new_pc->pc_number = ++data_prog->pc_number;
	copy_registry(new_pc, data_prog->pc);
	new_pc->next = data_prog->first_pc;
	data_prog->first_pc = new_pc;
	return (3);
}
