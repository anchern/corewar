/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:45:53 by achernys          #+#    #+#             */
/*   Updated: 2018/04/28 18:24:13 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*getstrcpy(char *str)
{
	char *strout;

	if (str == 0)
		return (0);
	strout = ft_strcpy(ft_strnew(ft_strlen(str)), str);
	return (strout);
}

char		*procc(int identifier, t_data *data, t_argptrsave *structarg)
{
	char	*strch;

	if ((identifier == 'C' || data->l == 1) && MB_CUR_MAX > 1)
		return (procwc(get_wchar(&structarg->argptrcurr)));
	strch = (char *)ft_memalloc(2);
	strch[0] = get_char(&structarg->argptrcurr);
	strch[1] = 0;
	return (strch);
}

static int	getlenwchar(wchar_t wchar)
{
	if (wchar < 128)
		return (1);
	else if (wchar > 127 && wchar < 2048)
		return (2);
	else if (wchar > 2047 && wchar < 65536)
		return (3);
	else if (wchar > 65535 && wchar < 2097152)
		return (4);
	return (0);
}

static void	wprecision(char *outstr, char *str, int precision, wchar_t *wstr)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = getlenwchar(wstr[i]);
	while (precision >= len)
	{
		ft_memcpy(&outstr[j], &str[j], (size_t)len);
		j += len;
		i++;
		precision -= len;
		len = getlenwchar(wstr[i]);
	}
}

char		*procs(int identifier, t_data *data, t_argptrsave *structarg)
{
	char	*outstr;
	char	*src;
	wchar_t *wstr;

	if ((identifier == 'S' || data->l == 1))
	{
		wstr = get_wstr(&structarg->argptrcurr);
		src = procwstr(wstr);
	}
	else
		src = getstrcpy(get_str(&structarg->argptrcurr));
	if (src == 0)
		return (0);
	if (data->prec > -1)
	{
		outstr = ft_strnew((size_t)data->prec);
		if (identifier == 'S' || data->l == 1)
			wprecision(outstr, src, data->prec, wstr);
		else
			ft_memcpy(outstr, src, (size_t)data->prec);
		ft_memdel((void **)&src);
		return (outstr);
	}
	return (src);
}
