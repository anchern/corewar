/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_and_set_numbers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:59:12 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/22 13:58:58 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

void		set_start_numbers(unsigned *free_numbers)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		free_numbers[i] = (unsigned)-(i + 1);
		i++;
	}
}

char		is_valid_number(t_player *players, t_player *current_player)
{
	if (players == 0)
		return (1);
	if (current_player->player_number < (unsigned)-4)
		return (0);
	if (current_player->player_number == players->player_number &&
		current_player != players)
		return (0);
	return (is_valid_number(players->next, current_player));
}

unsigned	get_free_number(unsigned *free_numbers)
{
	int			i;
	unsigned	out;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (free_numbers[i] != 0)
		{
			out = free_numbers[i];
			free_numbers[i] = 0;
			return (out);
		}
		i++;
	}
	too_many_players_err();
	return (0);
}

void		check_players_numbers(t_player *player, char quantity,
								unsigned *free_numbers)
{
	while (player != NULL)
	{
		if (player->player_number < (unsigned)-quantity ||
			player->player_number == 0)
			player->player_number = get_free_number(free_numbers);
		player = player->next;
	}
}

char		set_player_numbers(t_data_prog *data_prog, int start_arg, int argc,
							char **argv)
{
	t_player		*cur_player;
	unsigned		free_num[MAX_PLAYERS];
	char			quan_players;

	init_player_numbers_data(free_num, &cur_player, data_prog, &quan_players);
	while (start_arg < argc)
	{
		cur_player = create_new_player(data_prog, cur_player);
		if (!ft_strcmp(argv[start_arg], "-n"))
		{
			if (start_arg++ + 1 == argc)
				exit(ARG_ERR);
			check_num_flag(&(cur_player->player_number), argv, start_arg, 1);
			if (!is_valid_number(data_prog->player, cur_player))
				cur_player->player_number = get_free_number(free_num);
			free_num[-(int)cur_player->player_number - 1] = 0;
			start_arg++;
		}
		else
			cur_player->player_number = get_free_number(free_num);
		cur_player->file_name = argv[start_arg++];
		quan_players++;
	}
	check_players_numbers(data_prog->player, quan_players, free_num);
	return (quan_players);
}
