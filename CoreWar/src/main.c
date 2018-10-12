/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/10/12 18:25:58 by achernys         ###   ########.fr       */
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
	{
		ft_printf("%02d ", i);
	}
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





int main(int argc, char **argv)
{
	t_data_prog 	*data_prog;
	unsigned char	value;

	data_prog = data_prog_init();
	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
	set_players(data_prog, 1, argc, argv);
	print_field(data_prog->game_info, 0);
	current_cycle_to_die(data_prog);
}
