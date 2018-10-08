/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:25:49 by achernys          #+#    #+#             */
/*   Updated: 2018/10/03 20:07:58 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

header_t	*init_header(header_t *header)
{
	if (!(header = (header_t *)ft_memalloc(sizeof(header_t))))
		exit(INIT_ERR);
	return (header);
}

void	nulling_header(header_t *header)
{
	header->magic = 0;
	header->prog_size = 0;
}


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

void	nulling_player_and_gameinfo(t_player *player, t_game_info *game_info)
{
	if (player != 0)
	{
		player->alive_counter = 0;
		player->carry = 0;
		player->last_live = 0;
		player->player_number = 0;
		player->next = NULL;
		player->header = init_header(player->header);
		nulling_header(player->header);
		player->pc = init_pc();
		nulling_pc(player->pc, 0);

	}
	if (game_info != 0)
	{
		game_info->counter = 0;
		game_info->cycle_delta_counter = 0;
		game_info->max_checks_counter = 0;
		game_info->cycle_delta_counter = 0;
	}
}

t_options	*init_options(t_options *options)
{
	if (!(	options = (t_options *)ft_memalloc(sizeof(t_options))))
		exit(INIT_ERR);
	return (options);
}

t_arrays	*init_arrays(t_arrays *arrays)
{
	if (!(arrays = (t_arrays *)malloc(sizeof(t_arrays))))
		exit(INIT_ERR);
	return (arrays);
}

void	init_options_array(t_arrays **arrays)
{
	(*arrays)->options_array[0] = &d_options;
	(*arrays)->options_array[1] = &di_r_options;
	(*arrays)->options_array[2] = &r_ri_options;
	(*arrays)->options_array[3] = &r_r_r_options;
	(*arrays)->options_array[4] = &r_r_r_options;
	(*arrays)->options_array[5] = &rdi_rdi_r_options;
	(*arrays)->options_array[6] = &rdi_rdi_r_options;
	(*arrays)->options_array[7] = &rdi_rdi_r_options;
	(*arrays)->options_array[8] = &d_options;
	(*arrays)->options_array[9] = &rdi_rd_r_options;
	(*arrays)->options_array[10] = &r_rdi_rd_options;
	(*arrays)->options_array[11] = &d_options;
	(*arrays)->options_array[12] = &di_r_options;
	(*arrays)->options_array[13] = &rdi_rd_r_options;
	(*arrays)->options_array[14] = &d_options;
}

void	init_function_array(t_arrays **arrays)
{
	(*arrays)->functions_array[0] = &load_command;
	(*arrays)->functions_array[1] = &store_command;
	(*arrays)->functions_array[2] = &addition_command;
	(*arrays)->functions_array[3] = &substraction_command;
	(*arrays)->functions_array[4] = &and_function;
	(*arrays)->functions_array[5] = &or_function;
	(*arrays)->functions_array[6] = &xor_function;
	(*arrays)->functions_array[7] = &jump_function;
	(*arrays)->functions_array[8] = &load_index_function;
	(*arrays)->functions_array[9] = &store_index_function;
	(*arrays)->functions_array[10] = &fork_function;
	(*arrays)->functions_array[11] = &long_load_command;
	(*arrays)->functions_array[12] = &long_load_index_function;
	(*arrays)->functions_array[13] = &long_fork_function;
}

t_pc	*init_pc(void)
{
	t_pc *pc;

	if (!(pc = (t_pc *)malloc(sizeof(t_pc))))
		exit(INIT_ERR);
	return (pc);
}

void	nulling_pc(t_pc *pc, short pc_index)
{
	pc->next = 0;
	pc->pc_index = pc_index;
	pc->command = 0;
	pc->alive_label = 0;
	pc->time_todo = 0;
}

void	nulling_options(t_options *options)
{
	int i;

	i = 0;
	while (i < 3)
	{
		options->dir[i] = 0;
		options->reg[i] = 0;
		if (i < 2)
			options->ind[i] = 0;
		options->option_number[i] = 0;
		i++;
	}
}