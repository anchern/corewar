/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:08:11 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:10:07 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void		save_in_var(unsigned int *var, unsigned char *arr)
{
	*var = (*var | arr[0]) << 8;
	*var = (*var | arr[1]) << 8;
	*var = (*var | arr[2]) << 8;
	*var = *var | arr[3];
}

void		copy_field(t_game_info *game_info, unsigned char *field,
					int field_size, short start_position)
{
	int i;

	i = 0;
	while (i < field_size)
	{
		game_info->field[start_position++].value = field[i];
		i++;
	}
}

void		set_registry(t_pc *pc, unsigned int num)
{
	if (pc == 0)
		return ;
	pc->registry[0] = num;
	set_registry(pc->next, num + 1);
}

void		set_start_pc_index(t_pc *pc, char quantity, char i)
{
	if (pc->next == 0)
	{
		pc->pc_index = 0;
		return ;
	}
	pc->pc_index = (short)(FIELD_SIZE / quantity * i);
	set_start_pc_index(pc->next, quantity, i - (char)1);
}

void		init_player_numbers_data(unsigned *free_numbers,
									t_player **current_player,
									t_data_prog *data_prog,
									char *quantity_players)
{
	(*current_player) = data_prog->player;
	set_start_numbers(free_numbers);
	*quantity_players = 0;
}
