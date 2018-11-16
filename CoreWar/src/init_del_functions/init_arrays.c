/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:13:00 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 15:17:45 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_arrays	*init_arrays(t_arrays *arrays)
{
	if (!(arrays = (t_arrays *)malloc(sizeof(t_arrays))))
		exit(INIT_ERR);
	return (arrays);
}

void		init_options_array(t_arrays **arrays)
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

void		init_function_array(t_arrays **arrays)
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
