/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands6-10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:54:52 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:16:18 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

unsigned int	and_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;

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
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
		+ data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_and_function(data_prog, &result, a, b);
	return (result);
}

unsigned int	or_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;

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
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
		+ data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_or_function(data_prog, &result, a, b);
	return (result);
}

unsigned int	xor_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;

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
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
		data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_xor_function(data_prog, &result, a, b);
	return (result);
}

unsigned int	load_index_function(t_data_prog *data_prog)
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
	return (dop_load_index_function(data_prog, result, a, b));
}
