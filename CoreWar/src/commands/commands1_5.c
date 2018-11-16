/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands1-5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:54:57 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:14:09 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

unsigned int	alive_command(t_data_prog *data_prog)
{
	t_player *player_tmp;

	player_tmp = data_prog->first_player;
	data_prog->pc->alive_label = 1;
	while (player_tmp != NULL)
	{
		if (player_tmp->player_number == data_prog->pc->options->dir[0])
		{
			player_tmp->last_live = data_prog->game_info->counter;
			player_tmp->alive_counter++;
		}
		player_tmp = player_tmp->next;
	}
	return (5);
}

unsigned int	load_command(t_data_prog *data_prog)
{
	unsigned int result;

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
		data_prog->pc->options->ind[0] =
				(short)(data_prog->pc->options->ind[0] % IDX_MOD);
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

unsigned int	store_command(t_data_prog *data_prog)
{
	unsigned int result;

	result = 1;
	if (data_prog->pc->options->option_number[1] == 3)
	{
		uitobytes(data_prog->pc->registry[data_prog->pc->options->reg[0] - 1],
				data_prog->game_info->field,
			data_prog->pc->pc_index +
			(short)(data_prog->pc->options->ind[1] % IDX_MOD));
		result = 5;
	}
	else if (data_prog->pc->options->option_number[1] == 1)
	{
		data_prog->pc->registry[data_prog->pc->options->reg[1] - 1] =
				data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
		result = 4;
	}
	return (result);
}

unsigned int	addition_command(t_data_prog *data_prog)
{
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] =
			data_prog->pc->registry[data_prog->pc->options->reg[0] - 1]
			+ data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
	return (5);
}

unsigned int	substraction_command(t_data_prog *data_prog)
{
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] =
			data_prog->pc->registry[data_prog->pc->options->reg[0] - 1]
			- data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
	return (5);
}
