/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 17:01:57 by achernys          #+#    #+#             */
/*   Updated: 2018/05/08 16:11:41 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "ft_printf.h"

int		isnonzerodigit(int c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}

void	setarg(t_argptrsave *structarg, int num)
{
	size_t	j;

	j = 0;
	va_copy(structarg->argptrcurr, structarg->argptrstart);
	while ((int)j < num - 1)
	{
		va_arg(structarg->argptrcurr, void *);
		j++;
	}
}

t_data	*getdatastruct(void)
{
	t_data	*newdata;

	newdata = (t_data *)ft_memalloc(sizeof(t_data));
	newdata->zero = 0;
	newdata->space = 0;
	newdata->minus = 0;
	newdata->plus = 0;
	newdata->hashtag = 0;
	newdata->h = 0;
	newdata->z = 0;
	newdata->l = 0;
	newdata->bl = 0;
	newdata->j = 0;
	newdata->wstar = 0;
	newdata->pstar = 0;
	newdata->dollar = 0;
	newdata->width = 0;
	newdata->prec = -1;
	return (newdata);
}

void	procstar(t_data *data, t_argptrsave *sarg)
{
	size_t	j;
	int		res;

	if (data->dollar != 0)
	{
		j = 0;
		va_copy(sarg->argstar, sarg->argptrstart);
		while ((int)j < data->dollar - 1)
		{
			va_arg(sarg->argstar, int);
			j++;
		}
	}
	res = va_arg(data->dollar == 0 ? sarg->argptrcurr : sarg->argstar, int);
	if (data->pstar)
		data->prec = res < 0 ? -1 : res;
	else if (data->wstar)
	{
		if (res < 0)
		{
			data->minus = 1;
			res = -res;
		}
		data->width = (size_t)res;
	}
}

char	procdollar(const char *format, size_t savei, size_t *addi)
{
	if (format[savei - 1] == '.')
		return ('.');
	if (format[*addi] == '$')
	{
		*addi += 1;
		return ('$');
	}
	return (0);
}
