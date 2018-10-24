/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:53:07 by achernys          #+#    #+#             */
/*   Updated: 2018/10/24 11:55:19 by dlewando         ###   ########.fr       */
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

	value = data_prog->player->pc->command;
	if (value == 1)
	{
		data_prog->player->pc->pc_index +=
				alive_command(data_prog->player->pc->options, data_prog,
							  data_prog->game_info->counter);
	}
	else if (value > 1 && value <= 16)
	{
		if (value == 16)
		{
			ft_printf("Aff: %c\n", (data_prog->player->pc->registry[data_prog
			->player->pc->options->reg[0]] % 256));
			data_prog->player->pc->pc_index += 3;

		}
		else if (value == 9)
		{
			if (data_prog->player->pc->carry == 1)
				data_prog->player->pc->pc_index +=
					(short)((short)(data_prog->player->pc->options->dir[0]) %
					IDX_MOD);
			else
				data_prog->player->pc->pc_index += 3;
		}
		else
			data_prog->player->pc->pc_index +=
					(data_prog->arrays->functions_array[value - 2](
							data_prog->player->pc->options, data_prog->player,
							data_prog->game_info->field));
	}
	data_prog->player->pc->pc_index = true_value_pc_index(data_prog->player->pc->pc_index);
	nulling_options(data_prog->player->pc->options);
	data_prog->player->pc->command = 0;
}

static void	set_options(t_data_prog *data_prog)
{
	unsigned char value;
	char tmp;

	value = data_prog->player->pc->command;
	if (value == 1)
	{
		tmp = data_prog->arrays->options_array[value - 1](data_prog->player->pc->options,
				data_prog->game_info->field,
				data_prog->player->pc->pc_index + (short)1, 4);
	}
	else if (value > 1 && value <= 16)
	{
		tmp = data_prog->arrays->options_array[value - 1](data_prog->player->pc->options,
				data_prog->game_info->field,
				data_prog->player->pc->pc_index + (short)1, 2);
	}
	else
		tmp = 0;
	if (tmp == -1)
		execute_command(data_prog);
	else
	{
		data_prog->player->pc->pc_index += (unsigned char)(tmp + 2);
		data_prog->player->pc->command = 0;
	}

}

void get_command(t_data_prog *data_prog)
{
	if (data_prog->game_info->field[data_prog->player->pc->pc_index].value > 0 &&
		data_prog->game_info->field[data_prog->player->pc->pc_index].value < 17)
	{
		data_prog->player->pc->command =
				data_prog->game_info->field[data_prog->player->pc->pc_index].value;
		data_prog->player->pc->time_todo =
				data_prog->to_do_list[
						data_prog->game_info->field[data_prog->player->pc->pc_index].value -
						1] - (short)1;
	}
	else
		data_prog->player->pc->pc_index++;
}

static void	processing_pc(t_data_prog *data_prog)
{
	short	save_pc;
	char tmp = 0;

	save_pc = data_prog->player->pc->pc_index;
	if (data_prog->player->pc->command == 0)
		get_command(data_prog);
	else if (data_prog->player->pc->time_todo == 0)
	{
		if (data_prog->player->pc->command == 9)
			tmp = 1;
//		if (tmp == 1 && data_prog->player->pc->carry == 1)
//			;
//		else
//			ft_printf("command: %x\t\t\t", data_prog->player->pc->command);
		set_options(data_prog);
		if (tmp == 1 && data_prog->player->pc->carry == 1)
		{

		} else
		{
//			ft_printf("%#06x -> %#06x\n", save_pc,
//					  data_prog->player->pc->pc_index);
//			ft_printf("%#06x -> %#06x %i %i ", save_pc,
//					  data_prog->player->pc->pc_index,
//					  data_prog->player->pc->pc_index - save_pc,
//					  data_prog->game_info->counter);
//			ft_printf("reg: %x %x\n", data_prog->player->pc->registry[1],
//					  data_prog->player->pc->registry[2]);
		}
		get_command(data_prog);

	}
	else
		data_prog->player->pc->time_todo--;
	data_prog->player->pc->pc_index =
			true_value_pc_index(data_prog->player->pc->pc_index);
}

void	nulling_pc_label(t_pc *pc)
{
	while (pc != NULL)
	{
		pc->label = 0;
		pc = pc->next;
	}
}

static void	goround_pc(t_data_prog *data_prog)
{
	data_prog->player->first_pc = data_prog->player->pc;
	nulling_pc_label(data_prog->player->pc);
	while(1)
	{
		if (data_prog->player->pc->label == 1)
			break ;
		while (data_prog->player->pc != 0 && data_prog->player->pc->label == 0)
		{
			processing_pc(data_prog);
			data_prog->player->pc->label = 1;
			data_prog->player->pc = data_prog->player->pc->next;
		}
		data_prog->player->pc = data_prog->player->first_pc;
	}
//	if (data_prog->game_info->counter == 2534)
//	{
//		print_field(data_prog->game_info, 0);
//		exit(79);
//	}
}

void		goround_players(t_data_prog *data_prog)
{
	data_prog->first_player = data_prog->player;
	while(data_prog->player != 0)
	{
		goround_pc(data_prog);
		data_prog->player = data_prog->player->next;
	}
	data_prog->player = data_prog->first_player;
}
