/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:36 by achernys          #+#    #+#             */
/*   Updated: 2018/09/26 11:58:37 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

char	d_options(t_options *options, t_sell *field, short pc_i, char dir_size)
{
	pc_i = true_value_pc_index(pc_i);
	options->option_number[0] = 2;
	options->dir[0] = dir_size == 4 ? bytestoui(field, pc_i) :
									bytestos(field, pc_i);
	return (1);
}

char	di_r_options(t_options *opt, t_sell *field, short pc_i)
{
	pc_i = true_value_pc_index(pc_i);
	if ((field[pc_i].value >> 4 & 3) != 1 || (field[pc_i].value >> 6 != 2 &&
										field[pc_i].value >> 6 != 3))
		return (0);
	if (field[pc_i].value >> 6 == 2)
	{
		opt->option_number[0] = 2;
		opt->dir[0] = bytestoui(field, pc_i + 1);
		opt->option_number[1] = 1;
		opt->reg[1] = field[pc_i + 3].value > 16 ? 0 : field[pc_i + 3].value;
	}
	else if (field[pc_i].value >> 6 == 3)
	{
		opt->option_number[0] = 3;
		opt->ind[0] = bytestos(field, pc_i + 1);
		opt->option_number[1] = 1;
		opt->reg[1] = field[pc_i + 3].value > 16 ? 0 : field[pc_i + 3].value;
	}
	return (opt->reg[1] == 0 ? 0 : 1);
}

char	r_ri_options(t_options *opt, t_sell *field, short pc_i)
{
	pc_i = true_value_pc_index(pc_i);
	if (field[pc_i].value >> 6 != 1 || ((field[pc_i].value >> 4 & 3) != 1 &&
										(field[pc_i].value >> 4 & 3) != 3))
		return (0);
	opt->option_number[0] = 1;
	opt->reg[0] = field[pc_i + 1].value > 16 ? 0 : field[pc_i + 1].value;
	if (field[pc_i].value << 2 >> 6 == 3)
	{
		opt->option_number[1] = 3;
		opt->ind[1] = bytestos(field, pc_i + 2);
	}
	else
	{
		opt->option_number[1] = 1;
		opt->reg[1] = field[pc_i + 2].value > 16 ? 0 : field[pc_i + 2].value;
	}
	if (opt->reg[0] == 0 || (opt->option_number[1] == 1 && opt->reg[1] == 0))
		return (0);
	return (1);
}

char	r_r_r_options(t_options *options, t_sell *field, short pc_i)
{
	pc_i = true_value_pc_index(pc_i);
	if (field[pc_i].value >> 6 != 1 || (field[pc_i].value >> 4 & 3) != 1 ||
			(field[pc_i].value >> 2 & 3) != 1)
		return (0);
	options->reg[0] = field[pc_i + 1].value > 16 ? 0 : field[pc_i + 1].value;
	options->reg[1] = field[pc_i + 2].value > 16 ? 0 : field[pc_i + 2].value;
	options->reg[2] = field[pc_i + 3].value > 16 ? 0 : field[pc_i + 3].value;
	if (options->reg[0] == 0 || options->reg[1] == 0 || options->reg[2] == 0)
		return (0);
	options->option_number[0] = 1;
	options->option_number[1] = 1;
	options->option_number[2] = 1;
	return (1);
}

char	r_options(t_options *options, t_sell *field, short pc_i)
{
	pc_i = true_value_pc_index(pc_i);
	if (field[pc_i].value >> 6 != 1)
		return (0);
	options->option_number[0] = 1;
	options->reg[0] = field[pc_i + 1].value > 16 ? 0 : field[pc_i + 1].value;
	return (options->reg[1] == 0 ? 0 : 1);

}