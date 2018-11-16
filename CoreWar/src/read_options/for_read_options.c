/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_read_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 06:38:57 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 15:14:40 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

char	isrdi(unsigned char byte, char shift)
{
	if ((byte >> shift & 3) == 1 || (byte >> shift & 3) == 2 ||
		(byte >> shift & 3) == 3)
		return (1);
	return (0);
}

char	save_reg(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[(int)opt_num] = (char)1;
	opt->reg[(int)opt_num] = (char)(field[0].value > 16 ? 0 : field[0].value);
	if (opt->reg[(int)opt_num] == 0)
		return (0);
	return (1);
}

char	save_dir(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[(int)opt_num] = (char)2;
	opt->dir[(int)opt_num] = bytestoui(field, 0);
	return (1);
}

char	save_ind(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[(int)opt_num] = 3;
	opt->ind[(int)opt_num] = bytestos(field, 0);
	return (1);
}

char	add_indent(char arg, int dir_size)
{
	if (arg == 1)
		return (1);
	else if (arg == 2)
		return ((char)dir_size);
	else if (arg == 3)
		return (2);
	return (0);
}
