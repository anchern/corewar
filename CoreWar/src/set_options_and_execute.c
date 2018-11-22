/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options_and_execute.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 12:16:55 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:36:04 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

static void	value_between_1_and_17(int value, t_data_prog *data_prog)
{
	if (value == 16)
	{
		ft_printf("Aff: %c\n",
		(data_prog->pc->registry[(int)data_prog->pc->options->reg[0]] % 256));
		data_prog->pc->pc_index += 3;
	}
	else if (value == 9)
	{
		if (data_prog->pc->carry == 1)
			data_prog->pc->pc_index +=
					(short)((short)(data_prog->pc->options->dir[0]) %
							IDX_MOD);
		else
			data_prog->pc->pc_index += 3;
	}
	else
		data_prog->pc->pc_index +=
				data_prog->arrays->functions_array[value - 2](data_prog);
}

void		execute_command(t_data_prog *data_prog)
{
	unsigned char value;

	value = data_prog->pc->command;
	if (value == 1)
	{
		data_prog->pc->pc_index +=
				alive_command(data_prog);
	}
	else if (value > 1 && value <= 16)
		value_between_1_and_17(value, data_prog);
	data_prog->pc->pc_index = true_value_pc_index(data_prog->pc->pc_index);
	nulling_options(data_prog->pc->options);
	data_prog->pc->command = 0;
}

void		set_options(t_data_prog *data_prog)
{
	unsigned char	value;
	char			tmp;

	value = data_prog->pc->command;
	if (value == 1)
	{
		tmp = data_prog->arrays->options_array[value -
				1](data_prog->pc->options, data_prog->game_info->field,
										data_prog->pc->pc_index + (short)1, 4);
	}
	else if (value > 1 && value <= 16)
	{
		tmp = data_prog->arrays->options_array[value -
				1](data_prog->pc->options,
		data_prog->game_info->field, data_prog->pc->pc_index + (short)1, 2);
	}
	else
		tmp = 0;
	if (tmp == -1)
		execute_command(data_prog);
	else
	{
		data_prog->pc->pc_index += (unsigned char)(tmp + 2);
		data_prog->pc->command = 0;
	}
}
