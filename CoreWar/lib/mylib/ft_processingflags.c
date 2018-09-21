/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processingflags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:21:19 by achernys          #+#    #+#             */
/*   Updated: 2018/04/26 18:18:27 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Обработка данных (флаги, ширина, точность, номер аргумента).
*/

static int		isnonwidth(char format, t_data *data,
							int atoires, t_argptrsave *structarg)
{
	if (format == '.')
	{
		if (data->pstar)
		{
			procstar(data, structarg);
			data->pstar = 0;
			data->dollar = 0;
		}
		data->prec = atoires < 0 ? -1 : atoires;
		return (1);
	}
	if (format == '$')
	{
		if (data->pstar || data->wstar)
			data->dollar = atoires;
		else
			setarg(structarg, atoires);
		return (1);
	}
	return (0);
}

static void		processingdigit(const char *format, t_argptrsave *structarg,
								size_t *addi, t_data *data)
{
	size_t	savei;
	int		atoires;

	if (format[*addi] == '.')
		*addi += 1;
	savei = *addi;
	if ((atoires = getnum(format, structarg, addi, data)) < 0)
	{
		*addi = savei + 1;
		return ;
	}
	if (isnonwidth(procdollar(format, savei, addi), data, atoires, structarg))
		return ;
	if (atoires < 0)
		data->minus = 1;
	if (data->wstar)
	{
		procstar(data, structarg);
		data->wstar = 0;
		data->dollar = 0;
	}
	data->width = atoires > 0 ? (size_t)atoires : (size_t)-atoires;
}

static void		procindentation(char identifier, size_t *addi, t_data *data)
{
	if (identifier == '0')
		data->zero = 1;
	else if (identifier == ' ' && !data->plus)
		data->space = 1;
	else if (identifier == '+')
	{
		data->plus = 1;
		data->space = 0;
	}
	else if (identifier == '#')
		data->hashtag = 1;
	else if (identifier == '-')
		data->minus = 1;
	*addi += 1;
}

static void		procexpansion(const char *format, size_t *addi, t_data *data)
{
	if (format[*addi] == 'h')
	{
		data->h = (char)(data->h == 2 || data->h == 0 ? 1 : 2);
		*addi += 1;
	}
	else if (format[*addi] == 'l')
	{
		data->l = (char)(data->l == 2 || data->l == 0 ? 1 : 2);
		*addi += 1;
	}
	else if (format[*addi] == 'z')
	{
		data->z = 1;
		*addi += 1;
	}
	else if (format[*addi] == 'j')
	{
		data->j = 1;
		*addi += 1;
	}
	else if (format[*addi] == 'L')
	{
		data->bl = (char)(data->bl == 2 || data->bl == 0 ? 1 : 2);
		*addi += 1;
	}
}

void			processingflags(const char *format, t_argptrsave *structarg,
								size_t *addi, t_data *data)
{
	char	*param;
	char	*expansion;

	param = getexpflagstr();
	expansion = getexpansionstr();
	while ((ft_strchr(param, format[*addi]) || ft_isdigit(format[*addi])) &&
					format[*addi] != 0)
	{
		if (isnonzerodigit(format[*addi]) || format[*addi] == '.' ||
			format[*addi] == '*')
			processingdigit(format, structarg, addi, data);
		else if (ft_strchr("#0-+ ", format[*addi]))
			procindentation(format[*addi], addi, data);
		else if (ft_strchr(expansion, format[*addi]))
			procexpansion(format, addi, data);
	}
	if ((data->pstar || data->wstar) && format[*addi] != 0)
		procstar(data, structarg);
	ft_memdel((void **)&expansion);
	ft_memdel((void **)&param);
}
