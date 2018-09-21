/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forparse02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:13:57 by achernys          #+#    #+#             */
/*   Updated: 2018/05/10 13:55:59 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printspace(t_data *data, int len)
{
	int		i;
	int		addlen;

	i = (int)data->width - len;
	addlen = 0;
	while (i >= 0)
	{
		addlen += (int)write(1, data->zero > 0 && data->minus == 0 ? "0" :
								" ", 1);
		i--;
	}
	return (addlen);
}

static int	procstrnull(t_data *data)
{
	int		addlen;

	if (data->minus)
	{
		addlen = (int)write(1, "(null)", (size_t)(data->prec > -1 &&
					data->prec < 6 ? data->prec : 6));
		addlen += printspace(data, data->prec > -1 &&
				data->prec < 6 ? data->prec + 1 : 7);
	}
	else
	{
		addlen = printspace(data, data->prec > -1 &&
				data->prec < 6 ? data->prec + 1 : 7);
		addlen += (int)write(1, "(null)", (size_t)(data->prec > -1 &&
				data->prec < 6 ? data->prec : 6));
	}
	return (addlen);
}

int			printnullstr(t_data *data, char identifier)
{
	int		addlen;

	if (identifier == 'c' || identifier == 'C')
	{
		if (data->minus)
		{
			addlen = (int)write(1, "\0", 1);
			addlen += printspace(data, 2);
		}
		else
		{
			addlen = printspace(data, 2);
			addlen += (int)write(1, "\0", 1);
		}
	}
	else
	{
		return (procstrnull(data));
	}
	return (addlen);
}

char		*procdouble(char identifier, t_data *data, t_argptrsave *structarg)
{
	char	*argstr;
	char	*outstr;

	if (identifier == 'f' || identifier == 'F')
	{
		argstr = procf(identifier, data, structarg);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	else if (identifier == 'e' || identifier == 'E')
	{
		argstr = transformftoue(identifier, data, structarg);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	else
		return (0);
}
