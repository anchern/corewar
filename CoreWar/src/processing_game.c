/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:27:44 by achernys          #+#    #+#             */
/*   Updated: 2018/10/25 19:06:21 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

static char	exist_pc(t_player *player)
{
	if (player == 0)
		return (FALSE);
	if (player->pc != 0)
		return (TRUE);
	return (exist_pc(player->next));
}

void		cycle_to_die_reduce(t_data_prog *data_prog, int *cycle_to_die)
{
	if (data_prog->player->alive_counter != -1)
	{
		if (data_prog->game_info->counter - data_prog->player->last_live >
			*cycle_to_die)
			data_prog->player->alive_counter = -1;
		if (data_prog->player->alive_counter > 21)
		{
			data_prog->game_info->max_checks_counter = 0;
			*cycle_to_die = *cycle_to_die - CYCLE_DELTA;
		}
	}
	if (data_prog->game_info->max_checks_counter == 10)
	{
		*cycle_to_die = *cycle_to_die - CYCLE_DELTA;
		data_prog->game_info->max_checks_counter = 0;
	}
}

int			pc_number(t_pc *pc)
{
	if (pc == 0)
		return (0);
	return (pc_number(pc->next) + 1);
}

void		death_pc_delete(t_data_prog *data_prog)
{
	t_pc	*first_pc;
	t_pc	*removable_pc;
	t_pc	*tmp_pc;
	t_pc	*save_previous;
	char	flag;

	save_previous = 0;
	first_pc = data_prog->player->pc;
	tmp_pc = data_prog->player->pc;
	if (tmp_pc->alive_label == 1)
		flag = 1;
	else
		flag = 0;
	while (first_pc != 0)
	{
		if (save_previous != 0 && flag == 0)
		{
			tmp_pc = save_previous;
			flag = 1;
		}
		if (first_pc->alive_label == 0)
		{
			removable_pc = first_pc;
			first_pc = first_pc->next;
			if (save_previous != 0)
				save_previous->next = first_pc;
			free(removable_pc);
			removable_pc = 0;
		}
		if (first_pc != 0 && first_pc->alive_label == 1)
		{
			save_previous = first_pc;
			first_pc = first_pc->next;
		}
	}
	if (flag == 0 && save_previous != 0)
		tmp_pc = save_previous;
	else if (flag == 0)
		tmp_pc = 0;
	data_prog->player->pc = tmp_pc;
}

void		nulling_alive_pc(t_pc *pc, t_data_prog *data_prog)
{
	if (pc == 0)
		return ;
	pc->alive_label = 0;
	nulling_alive_pc(pc->next, data_prog);
}

void		current_cycle_to_die(t_data_prog *data_prog)
{
	int		cycle_to_die;
	int		current_i;

	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die > 0 && exist_pc(data_prog->player))
	{
		current_i = 0;
		while (current_i < cycle_to_die)
		{
			goround_players(data_prog);
			current_i++;
			data_prog->game_info->counter++;
		}
		data_prog->game_info->max_checks_counter++;
		cycle_to_die_reduce(data_prog, &cycle_to_die);
		death_pc_delete(data_prog);
		while (data_prog->player != 0)
		{
			nulling_alive_pc(data_prog->player->pc, data_prog);
			data_prog->player->alive_counter = 0;
			data_prog->player = data_prog->player->next;
		}
		data_prog->player = data_prog->first_player;
	}
	ft_putendl("");
	print_field(data_prog->game_info, data_prog->player->pc);
}