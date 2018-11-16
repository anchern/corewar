/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 06:22:20 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"






int main(int argc, char **argv)
{
	t_data_prog 	*data_prog;
	int 			last_alive;
	t_player		*winner;
	unsigned int	player_number;

	data_prog = data_prog_init();
	if (argc > 3 && ft_strcmp(argv[1], "-d") == 0)
	{
		data_prog->game_info->stop_game = ft_atoi(argv[2]);
		set_players(data_prog, 3, argc, argv);
	}
	else
		set_players(data_prog, 1, argc, argv);
	data_prog->first_player = data_prog->player;
	player_number = (unsigned)-1;
	while (data_prog->player != NULL)
	{
		if (data_prog->player->player_number == player_number)
		{
			ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n", -(int)data_prog->player->player_number,
					data_prog->player->header->prog_size, data_prog->player->header->prog_name, data_prog->player->header->comment);
			player_number--;
			data_prog->player = data_prog->first_player;
		}
		else
			data_prog->player = data_prog->player->next;
	}
	data_prog->player = data_prog->first_player;
	current_cycle_to_die(data_prog);
	last_alive = data_prog->player->last_live;
	winner = data_prog->player;
	while (data_prog->player != NULL)
	{
		if (data_prog->player->last_live >= last_alive)
		{
			last_alive = data_prog->player->last_live;
			winner = data_prog->player;
		}
		data_prog->player = data_prog->player->next;
	}
	ft_printf("Player %d, \"%s\", has won !\n", -(int)winner->player_number, winner->header->prog_name);
	free_memory(data_prog);
	return (0);
}
