/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 20:21:57 by achernys          #+#    #+#             */
/*   Updated: 2018/05/10 13:11:33 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char g_colors[33][2][15] = {
	{"red", "\033[31m"},
	{"green", "\033[32m"},
	{"yellow", "\033[33m"},
	{"blue", "\033[34m"},
	{"purple", "\033[35m"},
	{"cyan", "\033[36m"},
	{"black", "\033[30m"},
	{"white", "\033[37m"},
	{"b_red", "\033[41m"},
	{"b_green", "\033[42m"},
	{"b_yellow", "\033[43m"},
	{"b_blue", "\033[44m"},
	{"b_purple", "\033[45m"},
	{"b_cyan", "\033[46m"},
	{"b_black", "\033[40m"},
	{"b_white", "\033[47m"},
	{"bred", "\033[31;1m"},
	{"bgreen", "\033[32;1m"},
	{"byellow", "\033[33;1m"},
	{"bblue", "\033[34;1m"},
	{"bpurple", "\033[35;1m"},
	{"bblack", "\033[30;1m"},
	{"bcyan", "\033[36;1m"},
	{"bwhite", "\033[37;1m"},
	{"b_bred", "\033[41;1m"},
	{"b_bgreen", "\033[42;1m"},
	{"b_byellow", "\033[43;1m"},
	{"b_bblue", "\033[44;1m"},
	{"b_bpurple", "\033[45;1m"},
	{"b_bcyan", "\033[46;1m"},
	{"b_bblack", "\033[40;1m"},
	{"b_bwhite", "\033[47;1m"},
	{"eoc", "\033[0m"}
};

static void	printcurpart(int *len, size_t *i, size_t *lencurpart,
							const char *format)
{
	*len += write(1, &format[*i - *lencurpart], *lencurpart);
	*lencurpart = 0;
}

static int	iscolor(char *color)
{
	int		i;

	i = 0;
	while (i < 33)
	{
		if (ft_strcmp(color, g_colors[i][0]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	print_color(int i)
{
	if (i < 16)
	{
		write(1, g_colors[i][1], 5);
	}
	else if (i == 32)
	{
		write(1, g_colors[i][1], 4);
	}
	else
		write(1, g_colors[i][1], 7);
}

void		set_color(int *len, size_t *i, size_t *lencurpart,
						const char *format)
{
	size_t	iter;
	char	*color;
	int		colornum;

	iter = *i + 1;
	while (format[iter] != '}')
	{
		if (format[iter] == 0 || iter - *i - 1 >= 9)
			return ;
		iter++;
	}
	color = ft_strnew(iter - *i - 1);
	iter = 0;
	while (format[iter + *i + 1] != '}')
	{
		color[iter] = format[iter + *i + 1];
		iter++;
	}
	if ((colornum = iscolor(color)) > -1)
	{
		printcurpart(len, i, lencurpart, format);
		print_color(colornum);
		*i += iter + 2;
	}
	ft_memdel((void **)&color);
}
