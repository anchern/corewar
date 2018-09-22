/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 04:01:59 by achernys          #+#    #+#             */
/*   Updated: 2018/09/22 07:16:00 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

static char	save_hdir(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[opt_num] = 2;
	opt->dir[opt_num] = (unsigned)bytestos(field, 0);
	return (1);
}

char		rdi_rdi_r_options(t_options *opt, t_sell *field, short pc_i)
{
	char	(*save[3])(t_sell *, t_options *, char);
	int		indent;

	save[0] = &save_reg;
	save[1] = &save_dir;
	save[2] = &save_ind;
	indent = 1;
	pc_i = true_value_pc_index(pc_i);
	if(!isrdi(field[pc_i].value, 6) || !isrdi(field[pc_i].value, 4) ||
			field[pc_i].value << 4 >> 6 != 1)
		return (0);
	if (!save[(field[pc_i].value >> 6) - 1](&field[pc_i + indent], opt, 0))
		return (0);
	indent += add_indent(opt->option_number[0], 4);
	if (!save[(field[pc_i].value << 2 >> 6) - 1](&field[pc_i + indent], opt, 1))
		return (0);
	indent += add_indent(opt->option_number[1], 4);
	if (!save[0](&field[pc_i + indent], opt, 2))
		return (0);
	return (1);
}

char		rdi_rd_r_options(t_options *opt, t_sell *field, short pc_i)
{
	char	(*save[3])(t_sell *, t_options *, char);
	int		indent;

	save[0] = &save_reg;
	save[1] = &save_hdir;
	save[2] = &save_ind;
	indent = 1;
	pc_i = true_value_pc_index(pc_i);
	if (!isrdi(field[pc_i].value, 6) || (field[pc_i].value << 2 >> 6 != 1 &&
		field[pc_i].value << 2 >> 6 != 2) || field[pc_i].value << 4 >> 6 != 1)
		return (0);
	if (!save[(field[pc_i].value >> 6) - 1](&field[pc_i + indent], opt, 0))
		return (0);
	indent += add_indent(opt->option_number[0], 2);
	if (!save[(field[pc_i].value << 2 >> 6) - 1](&field[pc_i + indent], opt, 1))
		return (0);
	indent += add_indent(opt->option_number[0], 2);
	if (!save[0](&field[pc_i + indent], opt, 2))
		return (0);
	return (1);
}

char		r_rdi_rd_options(t_options *opt, t_sell *field, short pc_i)
{
	char	(*save[3])(t_sell *, t_options *, char);
	int		indent;

	save[0] = &save_reg;
	save[1] = &save_hdir;
	save[2] = &save_ind;
	indent = 1;
	pc_i = true_value_pc_index(pc_i);
	if(field[pc_i].value >> 6 != 1 || !isrdi(field[pc_i].value, 4) ||
		(field[pc_i].value << 4 >> 6 != 1 && field[pc_i].value << 4 >> 6 != 2))
		return (0);
	if (!save[(field[pc_i].value >> 6) - 1](&field[pc_i + indent], opt, 0))
		return (0);
	indent += add_indent(opt->option_number[0], 2);
	if (!save[(field[pc_i].value << 2 >> 6) - 1](&field[pc_i + indent], opt, 1))
		return (0);
	indent += add_indent(opt->option_number[1], 2);
	if (!save[0](&field[pc_i + indent], opt, 2))
		return (0);
	return (1);
}