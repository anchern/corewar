/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 07:23:43 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 07:23:43 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

void		free_player(t_player *player)
{
	if (player == NULL)
		return ;
	free_player(player->next);
	free((void *)player->header);
	free((void *)player);
}

void		free_pc(t_pc *pc)
{
	if (pc == NULL)
		return ;
	free_pc(pc->next);
	free((void *)pc->options);
	free((void *)pc);
}

void		free_memory(t_data_prog *data_prog)
{
	free(data_prog->game_info);
	free_player(data_prog->first_player);
	free_pc(data_prog->first_pc);
	free(data_prog->arrays);
	free(data_prog);
}
