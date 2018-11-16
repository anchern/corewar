/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:15:51 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 08:15:51 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

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
