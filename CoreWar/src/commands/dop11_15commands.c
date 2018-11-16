/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop11-15commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 07:04:44 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:20:23 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

unsigned int	dop_long_load_index_function(t_data_prog *data_prog,
											unsigned int result, unsigned
											int a, unsigned int b)
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
			bytestoui(data_prog->game_info->field,
					data_prog->pc->pc_index +
					(short)((short)(a + b) % IDX_MOD));
	return (result);
}

unsigned int	dop_store_index_function(t_data_prog *data_prog,
										unsigned int result, unsigned int b)
{
	unsigned int c;

	if (data_prog->pc->options->option_number[2] == 1)
	{
		result++;
		c = data_prog->pc->registry[data_prog->pc->options->reg[2] - 1];
	}
	else if (data_prog->pc->options->option_number[2] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[2] = (short)data_prog->pc->options->dir[2];
		c = data_prog->pc->options->dir[2];
	}
	else
		return (1);
	uitobytes(data_prog->pc->registry[data_prog->pc->options->reg[0] - 1],
			data_prog->game_info->field, data_prog->pc->pc_index +
										(short)((short)(b + c) % IDX_MOD));
	return (result);
}
