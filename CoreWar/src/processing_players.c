/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:53:07 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 10:37:58 by achernys         ###   ########.fr       */
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

void	print_part_field(t_game_info *game_info, int start, int end)
{
	while (start < end)
	{
		ft_printf("%02x", game_info->field[start].value);
		if (start != end - 1)
			ft_printf(" ");
		start++;
	}
}
void	print_pc_inform(t_data_prog *data_prog, unsigned char value,
							short	save_pc)
{
	ft_printf("P %4i\tcommand: %2x ", data_prog->pc->pc_number, value);
	if (value == 9 && data_prog->pc->carry == 1)
		ft_printf("OK");
	else if (value == 9 && data_prog->pc->carry == 0)
		ft_printf("KO");
	ft_printf("\t\tmovement: %4i\t", data_prog->pc->pc_index - save_pc);
	ft_printf("(%#06x -> %#06x) ", save_pc,
			  data_prog->pc->pc_index);
	if (value == 9)
		print_part_field(data_prog->game_info, save_pc, save_pc + 3);
	else
		print_part_field(data_prog->game_info, save_pc,
						 data_prog->pc->pc_index);
	ft_printf("\n");
}

void	goround_pc(t_data_prog *data_prog)
{
	unsigned char value;
	short	save_pc;

	data_prog->first_pc = data_prog->pc;
	while (data_prog->pc != 0)
	{
		save_pc = data_prog->pc->pc_index;
		value = data_prog->pc->command;
		if (data_prog->pc->time_todo == 0 && data_prog->pc->command != 0)
			data_prog->pc->action = 1;
		if (data_prog->pc->action == 0)
			get_command(data_prog);
		else if (data_prog->pc->action == 1)
		{
			set_options(data_prog);
			if (data_prog->game_info->flag_pc)
				print_pc_inform(data_prog, value, save_pc);
			data_prog->pc->action = 0;
		}
		else
			data_prog->pc->time_todo--;
		data_prog->pc = data_prog->pc->next;
	}
	data_prog->pc = data_prog->first_pc;
}
