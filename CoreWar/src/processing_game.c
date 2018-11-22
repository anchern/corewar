/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:27:44 by achernys          #+#    #+#             */
/*   Updated: 2018/11/22 14:37:18 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"
#include "../lib/mylib/get_next_line.h"

void		kill_players(t_data_prog *data_prog, int *sum)
{
	*sum = 0;
	while (data_prog->player != 0)
	{
		if (data_prog->player->alive_counter != -1)
		{
			if (data_prog->player->alive_counter != -1)
				*sum += data_prog->player->alive_counter;
			if (data_prog->player->alive_counter == 0)
				data_prog->player->alive_counter = -1;
		}
		data_prog->player = data_prog->player->next;
	}
}

void		cycle_to_die_reduce(t_data_prog *data_prog, int *cycle_to_die)
{
	int	sum;

	kill_players(data_prog, &sum);
	if (sum >= NBR_LIVE)
	{
		data_prog->game_info->max_checks_counter = 0;
		*cycle_to_die = *cycle_to_die - CYCLE_DELTA;
		if (data_prog->game_info->flag_i == 1)
			ft_printf("Cycle to die is now %d\n", *cycle_to_die);
	}
	data_prog->player = data_prog->first_player;
	if (data_prog->game_info->max_checks_counter == MAX_CHECKS)
	{
		*cycle_to_die = *cycle_to_die - CYCLE_DELTA;
		data_prog->game_info->max_checks_counter = 0;
		if (data_prog->game_info->flag_i == 1)
			ft_printf("Cycle to die is now %d\n", *cycle_to_die);
	}
}

static void	print_field_and_free(t_data_prog *data_prog)
{
	print_field(data_prog->game_info);
	free_memory(data_prog);
	exit(0);
}

void		dop_cycle_current_cycle_to_die(int *current_i, int cycle_to_die,
														t_data_prog *data_prog)
{
	char	*line;

	*current_i = 0;
	while ((*current_i)++ < cycle_to_die)
	{
		data_prog->game_info->counter++;
		if (data_prog->game_info->flag_i == 1)
			ft_printf("It is now cycle %d\n", data_prog->game_info->counter);
		goround_pc(data_prog);
		if (data_prog->game_info->counter == data_prog->game_info->stop_game ||
			data_prog->game_info->stop_game == 0)
			print_field_and_free(data_prog);
		else if (data_prog->game_info->flag_s != 0 &&
			data_prog->game_info->counter % data_prog->game_info->flag_s == 0)
		{
			print_field(data_prog->game_info);
			get_next_line(0, &line);
			if (ft_atoi(line) > 0)
				data_prog->game_info->flag_s = ft_atoi(line);
			free(line);
		}
	}
}

void		current_cycle_to_die(t_data_prog *data_prog)
{
	int			cycle_to_die;
	int			current_i;

	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die > 0 && data_prog->pc != 0)
	{
		dop_cycle_current_cycle_to_die(&current_i, cycle_to_die, data_prog);
		data_prog->game_info->max_checks_counter++;
		cycle_to_die_reduce(data_prog, &cycle_to_die);
		death_pc_delete(data_prog);
		nulling_alive_pc(data_prog->pc, data_prog);
		while (data_prog->player != 0)
		{
			if (data_prog->player->alive_counter != -1)
				data_prog->player->alive_counter = 0;
			data_prog->player = data_prog->player->next;
		}
		data_prog->player = data_prog->first_player;
	}
}
