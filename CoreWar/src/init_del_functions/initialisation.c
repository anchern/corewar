/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:25:49 by achernys          #+#    #+#             */
/*   Updated: 2018/10/13 03:31:42 by dlewando         ###   ########.fr       */
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
	(*arrays)->options_array[15] = &r_options;
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
	(*arrays)->functions_array[7] = 0;
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
	int i;

	i = 0;
	while (i < 16)
	{
		pc->registry[i] = 0;
		i++;
	}
	pc->carry = 0;
	pc->next = 0;
	pc->action = 0;
	pc->pc_index = pc_index;
	pc->options = init_options(pc->options);
	nulling_options(pc->options);
	pc->command = 0;
	pc->alive_label = 0;
	pc->time_todo = 0;
	pc->pc_number = 0;

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

void		init_time_to_do_list(unsigned short *to_do_list)
{
	to_do_list[0] = (unsigned short)10;
	to_do_list[1] = (unsigned short)5;
	to_do_list[2] = (unsigned short)5;
	to_do_list[3] = (unsigned short)10;
	to_do_list[4] = (unsigned short)10;
	to_do_list[5] = (unsigned short)6;
	to_do_list[6] = (unsigned short)6;
	to_do_list[7] = (unsigned short)6;
	to_do_list[8] = (unsigned short)20;
	to_do_list[9] = (unsigned short)25;
	to_do_list[10] = (unsigned short)25;
	to_do_list[11] = (unsigned short)800;
	to_do_list[12] = (unsigned short)10;
	to_do_list[13] = (unsigned short)50;
	to_do_list[14] = (unsigned short)1000;
	to_do_list[15] = (unsigned short)2;
}

t_data_prog	*data_prog_init(void)
{
	t_data_prog *data_prog;

	if (!(data_prog = (t_data_prog *)ft_memalloc(sizeof(t_data_prog))))
		exit(INIT_ERR);
	init_time_to_do_list(data_prog->to_do_list);
	data_prog->game_info = init_game_info();
	data_prog->player = init_player();
	data_prog->arrays = init_arrays(data_prog->arrays);
	nulling_player_and_gameinfo(data_prog->player, data_prog->game_info);
	init_options_array(&data_prog->arrays);
	init_function_array(&data_prog->arrays);
	data_prog->first_pc = 0;
	data_prog->pc = init_pc();
	nulling_pc(data_prog->pc, 0);
	data_prog->pc->pc_number = 1;
	data_prog->pc_number = 1;

	return (data_prog);
}
//
//t_exe_pc	*exe_pc_init(t_pc *pc)
//{
//	t_exe_pc	*exe_pc;
//
//	if (!(exe_pc = (t_exe_pc *)ft_memalloc(sizeof(t_exe_pc))))
//		exit(INIT_ERR);
//	exe_pc->pc = pc;
//	exe_pc->pc_number = pc->pc_number;
//	exe_pc->next = NULL;
//	return (exe_pc);
//}