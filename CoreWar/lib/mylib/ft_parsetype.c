/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsetype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:55:08 by achernys          #+#    #+#             */
/*   Updated: 2018/05/09 18:57:24 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fixnumnotaticon(char **formatstr, char *str, t_data *data,
								char identifier)
{
	if (data->zero == 1 && data->minus == 0 &&
			(str[0] == ' ' || str[0] == '-' || str[0] == '+'))
	{
		ft_strchr(*formatstr, str[0])[0] = '0';
		(*formatstr)[0] = str[0];
	}
	else if (((identifier == 'x' || identifier == 'X') && data->hashtag) ||
			identifier == 'p')
	{
		if (ft_strlen(str) == 1 && str[0] == '0')
			return ;
		if (data->zero == 1 && data->minus == 0)
		{
			ft_strchr(*formatstr, str[1])[0] = '0';
			(*formatstr)[1] = str[1];
		}
	}
}

char		*addspace(char *src, t_data *data, char identifier)
{
	char	*strout;
	size_t	i;
	int		j;

	strout = ft_strnew(data->width == 0 ? ++data->width : data->width);
	ft_memset((void *)strout, (char)(data->zero == 1 && data->minus == 0 ?
					'0' : ' '), data->width);
	if (src == 0)
	{
		strout[data->minus == 1 ? 0 : data->width - 1] =
				(char)(ft_strchr("OoxX", identifier) ? ' ' : identifier);
		return (strout);
	}
	i = data->minus == 0 ? data->width - 1 : 0;
	j = data->minus == 0 ? (int)ft_strlen(src) - 1 : 0;
	while (j >= 0 && (size_t)j < ft_strlen(src))
	{
		strout[i] = src[j];
		j = data->minus == 0 ? j - 1 : j + 1;
		i = data->minus == 0 ? i - 1 : i + 1;
	}
	if (ft_strchr("diDFEGAfegaxXp", identifier))
		fixnumnotaticon(&strout, src, data, identifier);
	return (strout);
}

char		*getargstr(char identifier, t_data *data, t_argptrsave *structarg)
{
	if (identifier == 0)
		return (0);
	if (ft_strchr("diDuUxXoObp", identifier))
		return (procdig(identifier, data, structarg));
	if (ft_strchr("cCsS", identifier))
		return (proctext(identifier, data, structarg));
	if (ft_strchr("fFaAeEgG", identifier))
		return (procdouble(identifier, data, structarg));
	return (addspace(0, data, identifier));
}
