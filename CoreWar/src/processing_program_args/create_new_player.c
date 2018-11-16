/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:06:28 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:08:06 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_player	*create_new_player(t_data_prog *data_prog, t_player *current_player)
{
	t_player		*new_player;
	t_pc			*new_pc;

	if (current_player->player_number != 0)
	{
		new_player = init_player();
		nulling_player_and_gameinfo(new_player, 0);
		new_player->next = current_player;
		current_player = new_player;
		data_prog->player = new_player;
		new_pc = init_pc();
		nulling_pc(new_pc, 0);
		new_pc->pc_number = ++data_prog->pc_number;
		if (data_prog->pc == 0)
			data_prog->pc = new_pc;
		else
		{
			new_pc->next = data_prog->pc;
			data_prog->pc = new_pc;
		}
	}
	return (current_player);
}
