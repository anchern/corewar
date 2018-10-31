/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:53:07 by achernys          #+#    #+#             */
/*   Updated: 2018/10/27 00:49:07 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

void	copy_registry(t_pc *new_pc, t_pc *pc)
{
	int i;

	i = 0;
	while (i < 16)
	{
		new_pc->registry[i] = pc->registry[i];
		i++;
	}
}

static void	execute_command(t_data_prog *data_prog)
{
	unsigned char value;

	value = data_prog->pc->command;
	if (value == 1)
	{
		data_prog->pc->pc_index +=
				alive_command(data_prog);
	}
	else if (value > 1 && value <= 16)
	{
		if (value == 16)
		{
			ft_printf("Aff: %c\n", (data_prog->pc->registry[data_prog->pc->options->reg[0]] % 256));
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
	data_prog->pc->pc_index = true_value_pc_index(data_prog->pc->pc_index);
	nulling_options(data_prog->pc->options);
	data_prog->pc->command = 0;
}

static void	set_options(t_data_prog *data_prog)
{
	unsigned char value;
	char tmp;


	value = data_prog->pc->command;
	if (value == 1)
	{
		tmp = data_prog->arrays->options_array[value - 1](data_prog->pc->options,
				data_prog->game_info->field,
				data_prog->pc->pc_index + (short)1, 4);
	}
	else if (value > 1 && value <= 16)
	{
		tmp = data_prog->arrays->options_array[value - 1](data_prog->pc->options,
				data_prog->game_info->field,
				data_prog->pc->pc_index + (short)1, 2);
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

void get_command(t_data_prog *data_prog)
{
	if (data_prog->game_info->field[data_prog->pc->pc_index].value > 0 &&
		data_prog->game_info->field[data_prog->pc->pc_index].value < 17)
	{
		data_prog->pc->command =
				data_prog->game_info->field[data_prog->pc->pc_index].value;
		data_prog->pc->time_todo =
				data_prog->to_do_list[
						data_prog->game_info->field[data_prog->pc->pc_index].value -
						1] - 2;
		data_prog->pc->action = 2;
	}
	else
		data_prog->pc->pc_index++;

	data_prog->pc->pc_index =
			true_value_pc_index(data_prog->pc->pc_index);
}


void	goround_pc(t_data_prog *data_prog)
{
	short	save_pc;
	short	save_cmd;
	unsigned char value;

	data_prog->first_pc = data_prog->pc;
	while (data_prog->pc != 0)
	{
		save_pc = data_prog->pc->pc_index;
		save_cmd = data_prog->pc->command;
		value = data_prog->pc->command;
		if (data_prog->pc->time_todo == 0 && data_prog->pc->command != 0)
			data_prog->pc->action = 1;
		if (data_prog->pc->action == 0)
			get_command(data_prog);
		else if (data_prog->pc->action == 1)
		{
			set_options(data_prog);
//			if (value == 9 && data_prog->pc->carry == 1)
//				;
////			ft_printf("P %4i | ", data_prog->pc->pc_number);
//			else
//			{
////			if (data_prog->pc->command == 9)
////				ft_printf("carry = %d ", data_prog->pc->carry);
//				ft_printf("P %4i\tcommand: %x\t\t\t", data_prog->pc->pc_number, save_cmd);
//				ft_printf("%#06x -> %#06x %i %i ", save_pc,
//						  data_prog->pc->pc_index,
//						  data_prog->pc->pc_index - save_pc,
//						  data_prog->game_info->counter);
//				ft_printf("reg: %x %x\n", data_prog->pc->registry[1],
//						  data_prog->pc->registry[2]);
//			}
			data_prog->pc->action = 0;
		}
		else
			data_prog->pc->time_todo--;

		data_prog->pc = data_prog->pc->next;
	}
	data_prog->pc = data_prog->first_pc;
}
