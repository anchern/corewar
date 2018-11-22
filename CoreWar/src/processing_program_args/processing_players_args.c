/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:34:51 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 14:27:23 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

void		print_players_on_field(t_player *current_player,
								unsigned int player_number,
								t_data_prog *data_prog)
{
	int		fd;

	while (current_player != NULL)
	{
		if (current_player->player_number == player_number)
		{
			if ((fd = read_header(data_prog->game_info, current_player->header,
								current_player->file_name,
								data_prog->pc->pc_index)))
			{
				ft_printf("{red}Error in file %s{eoc}\n",
						current_player->file_name);
				close(fd);
				exit(FILE_INFORM_ERR);
			}
			player_number++;
			current_player = data_prog->player;
			data_prog->pc = data_prog->pc->next;
		}
		else
			current_player = current_player->next;
	}
}

void		set_players(t_data_prog *data_prog,
						int start_arg, int argc, char **argv)
{
	t_player		*current_player;
	char			quantity_players;
	unsigned int	player_number;

	quantity_players = set_player_numbers(data_prog, start_arg, argc, argv);
	current_player = data_prog->player;
	set_registry(data_prog->pc, (unsigned int)-quantity_players);
	set_start_pc_index(data_prog->pc, quantity_players,
						(char)(quantity_players - 1));
	player_number = (unsigned)-quantity_players;
	data_prog->first_pc = data_prog->pc;
	print_players_on_field(current_player, player_number, data_prog);
	data_prog->pc = data_prog->first_pc;
}
