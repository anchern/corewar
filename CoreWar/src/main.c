/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/10/13 00:49:02 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

void	print_pc(t_game_info *game_info, t_pc *pc)
{
	if (pc == 0)
		return ;
	game_info->field[pc->pc_index].owner = 1;
	print_pc(game_info, pc->next);
}

void	nulling_print_pc(t_game_info *game_info, t_pc *pc)
{
	if (pc == 0)
		return ;
	game_info->field[pc->pc_index].owner = 0;
	nulling_print_pc(game_info, pc->next);
}

void	print_field(t_game_info *game_info, t_pc *pc)
{
	int		i;

	i = 0;
	ft_printf("%9c", ' ');
	for (int i = 0; i < 64; i++)
		ft_printf("%02x ", i);
	ft_printf("\n");
	for (int i = 0; i < 64 * 3 + 8; i++)
		ft_printf("-");
	ft_printf("\n");
	print_pc(game_info, pc);
	ft_printf("0x0000 : ");
	while (i < FIELD_SIZE)
	{
//		if (game_info->field[i].value == 2 || (game_info->field[i].value >= 4 && game_info->field[i].value <= 8) || game_info->field[i].value == 10 || game_info->field[i].value == 13 || game_info->field[i].value == 14)
//			ft_printf("{red}%02x{eoc}", game_info->field[i].value);
//		else if (game_info->field[i].owner == 1)
//			ft_printf("{blue}%02x{eoc}", game_info->field[i].value);
//		else
		ft_printf("%02x", game_info->field[i].value);
		if (!((i + 1) % 64))
		{
			ft_printf("\n");
			if (i != FIELD_SIZE - 1)
				ft_printf("%#06x : ", i + 1);
		}
		else
			ft_printf(" ");
		i++;
	}
	nulling_print_pc(game_info, pc);
}

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
	t_data_prog 	*data_prog;
	
	data_prog = data_prog_init();
	if (ft_strcmp(argv[1], "-d") == 0)
	{
		data_prog->game_info->stop_game = ft_atoi(argv[2]);
		set_players(data_prog, 3, argc, argv);
	}
	else
		set_players(data_prog, 1, argc, argv);
	data_prog->first_player = data_prog->player;
	print_players(data_prog);
	current_cycle_to_die(data_prog);
	print_winner(data_prog);
	free_memory(data_prog);
	return (0);
}
