/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_read_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 06:38:57 by achernys          #+#    #+#             */
/*   Updated: 2018/10/12 23:13:02 by achernys         ###   ########.fr       */
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
	opt->option_number[opt_num] = 1;
	opt->reg[opt_num] = field[0].value > 16 ? 0 : field[0].value;
	if (opt->reg[opt_num] == 0)
		return (0);
	return (1);
}

char	save_dir(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[opt_num] = 2;
	opt->dir[opt_num] = bytestoui(field, 0);
	return (1);
}

char	save_ind(t_sell *field, t_options *opt, char opt_num)
{
	opt->option_number[opt_num] = 3;
	opt->ind[opt_num] = bytestos(field, 0);
	return (1);
}


char		add_indent(char arg, int dir_size)
{
	if (arg == 1)
		return (1);
	else if (arg == 2)
		return (dir_size);
	else if (arg == 3)
		return (2);
	return (0);
}

