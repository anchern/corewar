/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 04:01:59 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 15:14:40 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

char		get_indent_pc(unsigned char codage_octal, char dir_size)
{
	char indent;

	indent = 0;
	if (codage_octal < 4)
		return (0);
	if (FIRST_CODE(codage_octal) == 1)
		indent++;
	else if (FIRST_CODE(codage_octal) == 2)
		indent += dir_size;
	else if (FIRST_CODE(codage_octal) == 3)
		indent += 2;
	if (MIDDLE_CODE(codage_octal) == 1)
		indent++;
	else if (MIDDLE_CODE(codage_octal) == 2)
		indent += dir_size;
	else if (MIDDLE_CODE(codage_octal) == 3)
		indent += 2;
	if (LAST_CODE(codage_octal) == 1)
		indent++;
	else if (LAST_CODE(codage_octal) == 2)
		indent += dir_size;
	else if (LAST_CODE(codage_octal) == 3)
		indent += 2;
	return (indent);
}

static char	save_hdir(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[(int)opt_num] = (char)2;
	opt->dir[(int)opt_num] = (unsigned)bytestos(field, 0);
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
	if (!isrdi(field[pc_i].value, 6) || !isrdi(field[pc_i].value, 4) ||
			(field[pc_i].value >> 2 & 3) != 1)
		return (get_indent_pc(field[pc_i].value, 4));
	if (!save[(field[pc_i].value >> 6) - 1](&field[true_value_pc_index(pc_i +
	indent)], opt, 0))
		return (get_indent_pc(field[pc_i].value, 4));
	indent += add_indent(opt->option_number[0], 4);
	if (!save[(field[pc_i].value >> 4 & 3) - 1](&field
	[true_value_pc_index(pc_i + indent)], opt, 1))
		return (get_indent_pc(field[pc_i].value, 4));
	indent += add_indent(opt->option_number[1], 4);
	if (!save[0](&field[true_value_pc_index(pc_i + indent)], opt, 2))
		return (get_indent_pc(field[pc_i].value, 4));
	return (-1);
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
	if (!isrdi(field[pc_i].value, 6) || ((field[pc_i].value >> 4 & 3) != 1 &&
		(field[pc_i].value >> 4 & 3) != 2) || (field[pc_i].value >> 2 & 3) != 1)
		return (get_indent_pc(field[pc_i].value, 2));
	if (!save[(field[pc_i].value >> 6) - 1](&field[true_value_pc_index(pc_i +
	indent)], opt, 0))
		return (get_indent_pc(field[pc_i].value, 2));
	indent += add_indent(opt->option_number[0], 2);
	if (!save[(field[pc_i].value >> 4 & 3) - 1](&field[true_value_pc_index(pc_i
	+ indent)], opt, 1))
		return (get_indent_pc(field[pc_i].value, 2));
	indent += add_indent(opt->option_number[1], 2);
	if (!save[0](&field[pc_i + indent], opt, 2))
		return (get_indent_pc(field[pc_i].value, 2));
	return (-1);
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
	if (field[pc_i].value >> 6 != 1 || !isrdi(field[pc_i].value, 4) ||
		((field[pc_i].value >> 2 & 3) != 1 &&
				(field[pc_i].value >> 2 & 3) != 2))
		return (get_indent_pc(field[pc_i].value, 2));
	if (!save[(field[pc_i].value >> 6) - 1](&field[true_value_pc_index(pc_i +
										indent)], opt, 0))
		return (get_indent_pc(field[pc_i].value, 2));
	indent += add_indent(opt->option_number[0], 2);
	if (!save[(field[pc_i].value >> 4 & 3) - 1](&field[true_value_pc_index(pc_i
					+ indent)], opt, 1))
		return (get_indent_pc(field[pc_i].value, 2));
	indent += add_indent(opt->option_number[1], 2);
	if (!save[(field[pc_i].value >> 2 & 3) - 1](&field[true_value_pc_index(pc_i
								+ indent)], opt, 2))
		return (get_indent_pc(field[pc_i].value, 2));
	return (-1);
}
