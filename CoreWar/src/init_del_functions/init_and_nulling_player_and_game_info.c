/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_nulling_player_and_game_info.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:10:29 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 09:02:23 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_game_info	*init_game_info(void)
{
	t_game_info *game_info;

	if (!(game_info = (t_game_info *)ft_memalloc(sizeof(t_game_info))))
		exit(INIT_ERR);
	return (game_info);
}

t_player	*init_player(void)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		exit(INIT_ERR);
	player->player_number = 0;
	player->next = NULL;
	return (player);
}

void		nulling_player_and_gameinfo(t_player *player,
										t_game_info *game_info)
{
	if (player != 0)
	{
		player->alive_counter = 0;
		player->last_live = 0;
		player->player_number = 0;
		player->file_name = 0;
		player->next = NULL;
		player->header = init_header(player->header);
		nulling_header(player->header);
	}
	if (game_info != 0)
	{
		game_info->counter = 0;
		game_info->max_checks_counter = 0;
		game_info->stop_game = -1;
		game_info->flag_s = 0;
		game_info->flag_m = 0;
		game_info->flag_i = 0;
		game_info->flag_pc = 0;
	}
}
