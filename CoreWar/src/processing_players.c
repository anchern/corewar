/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:53:07 by achernys          #+#    #+#             */
/*   Updated: 2018/10/13 01:35:26 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

static void	get_command(t_data_prog *data_prog)
{
	unsigned char value;
	char tmp;

	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
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
	{
		data_prog->player->pc->pc_index++;
		return ;
	}
	if (tmp == -1)
	{
		data_prog->player->pc->command = value;
		data_prog->player->pc->time_todo = data_prog->to_do_list[value - 1];
	}
	else
	{
		data_prog->player->pc->jump = (unsigned char)(tmp + 2);
		data_prog->player->pc->time_todo = data_prog->to_do_list[value - 1];
	}
	data_prog->player->pc->time_todo--;
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
			ft_printf("Aff: %c\n", data_prog->player->registry[data_prog->player->pc->options->reg[0]]);
			data_prog->player->pc->pc_index += 3;
		}
		else if (value == 9)
		{
			data_prog->player->pc->pc_index +=
					(short)(data_prog->arrays->functions_array[value - 2](
							data_prog->player->pc->options, data_prog->player,
							data_prog->game_info->field));
			data_prog->player->pc->pc_index = true_value_pc_index(data_prog->player->pc->pc_index);
		}
		else
			data_prog->player->pc->pc_index +=
					(data_prog->arrays->functions_array[value - 2](
							data_prog->player->pc->options, data_prog->player,
							data_prog->game_info->field));
	}
	nulling_options(data_prog->player->pc->options);
	data_prog->player->pc->command = 0;
}

static void	processing_pc(t_data_prog *data_prog)
{
	short	save_pc;

	save_pc = data_prog->player->pc->pc_index;
	if (data_prog->player->pc->command == 0)
		get_command(data_prog);
	else if (data_prog->player->pc->time_todo == 0)
	{
		if (data_prog->player->pc->jump != 0)
		{
			data_prog->player->pc->pc_index += data_prog->player->pc->jump;
			data_prog->player->pc->jump = 0;
		}
		else
			execute_command(data_prog);
		ft_printf("%x %x %i %i command: %x\t\t\treg: %x\n", save_pc, data_prog->player->pc->pc_index, data_prog->player->pc->pc_index - save_pc, data_prog->game_info->counter, data_prog->game_info->field[save_pc].value, data_prog->player->registry[1]);
		data_prog->player->pc->time_todo = 0;
		get_command(data_prog);
	}
	else
		data_prog->player->pc->time_todo--;
	data_prog->player->pc->pc_index =
			true_value_pc_index(data_prog->player->pc->pc_index);
}
//
//void	nulling_pc_label(t_pc *pc)
//{
//
//}

static void	goround_pc(t_data_prog *data_prog)
{
	int		i;
	t_pc	*last_pc_p;
	char	flag;

	i = 0;
	data_prog->player->first_pc = data_prog->player->pc;
	last_pc_p = data_prog->player->pc;
	while (data_prog->player->pc != 0)
	{
		processing_pc(data_prog);
		data_prog->player->pc = data_prog->player->pc->next;
		i++;
	}
	while (1)
	{

		if (data_prog->player->first_pc == last_pc_p)
			break ;
		data_prog->player->pc = data_prog->player->first_pc;
	}
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
