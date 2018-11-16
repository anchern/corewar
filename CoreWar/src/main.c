/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 11:07:37 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"
#include "../lib/mylib/get_next_line.h"

void		print_winner(t_data_prog *data_prog)
{
	int 			last_alive;
	t_player		*winner;

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
	ft_printf("Player %d, \"%s\", has won !\n", -(int)winner->player_number,
			winner->header->prog_name);
}

void		print_players(t_data_prog *data_prog)
{
	unsigned int	player_number;

	data_prog->first_player = data_prog->player;
	player_number = (unsigned)-1;
	while (data_prog->player != NULL)
	{
		if (data_prog->player->player_number == player_number)
		{
			ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
					-(int)data_prog->player->player_number,
					  data_prog->player->header->prog_size,
					  data_prog->player->header->prog_name,
					  data_prog->player->header->comment);
			player_number--;
			data_prog->player = data_prog->first_player;
		}
		else
			data_prog->player = data_prog->player->next;
	}
	data_prog->player = data_prog->first_player;
}

int main(int argc, char **argv)
{
	int			tmp;
	t_data_prog *data_prog;
	int			start_player_arg_num;
	char		*line;

	if (argc == 1)
		print_usage();
	data_prog = data_prog_init();
	start_player_arg_num = get_flags(data_prog, argv, argc);
	set_players(data_prog, start_player_arg_num, argc, argv);
	print_players(data_prog);
	if (data_prog->game_info->flag_s > 0)
	{
		print_field(data_prog->game_info);
		get_next_line(0, &line);
		if ((tmp = ft_atoi(line)) > 0)
			data_prog->game_info->flag_s = tmp;
		free(line);
	}
	current_cycle_to_die(data_prog);
	print_winner(data_prog);
	free_memory(data_prog);
	return (0);
}
