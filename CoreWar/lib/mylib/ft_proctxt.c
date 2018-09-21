/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proctxt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:06:34 by achernys          #+#    #+#             */
/*   Updated: 2018/05/03 19:52:05 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*procswc(wchar_t c)
{
	char	*outstr;

	outstr = 0;
	if (c < 128)
	{
		outstr = ft_strnew(1);
		outstr[0] = (char)c;
	}
	if (c > 127 && c < 2048)
	{
		outstr = ft_strnew(2);
		outstr[0] = (char)((c >> 6) + 192);
		outstr[1] = (char)((c & 63) + 128);
	}
	return (outstr);
}

static char	*procbwc(wchar_t c)
{
	char	*outstr;

	outstr = 0;
	if (c > 2047 && c < 65536)
	{
		outstr = ft_strnew(3);
		outstr[0] = (char)((c >> 12) + 224);
		outstr[1] = (char)(((c >> 6) & 63) + 128);
		outstr[2] = (char)((c & 63) + 128);
	}
	if (c > 65535 && c < 2097152)
	{
		outstr = ft_strnew(4);
		outstr[0] = (char)((c >> 18) + 240);
		outstr[1] = (char)(((c >> 12) & 63) + 128);
		outstr[2] = (char)(((c >> 6) & 63) + 128);
		outstr[3] = (char)((c & 63) + 128);
	}
	return (outstr);
}

char		*procwc(wchar_t c)
{
	char	*outstr;

	if (c == 0)
		return (0);
	if (c < 2048)
		outstr = procswc(c);
	else
		outstr = procbwc(c);
	return (outstr);
}

static int	ft_wstrlen(wchar_t *wstr)
{
	int		i;
	int		len;

	if (wstr == 0 || *wstr == 0)
		return (0);
	len = 0;
	i = 0;
	while (wstr[i] != 0)
	{
		if (wstr[i] < 128)
			len++;
		else if (wstr[i] > 127 && wstr[i] < 2048)
			len += 2;
		else if (wstr[i] > 2047 && wstr[i] < 65536)
			len += 3;
		else if (wstr[i] > 65535 && wstr[i] < 2097152)
			len += 4;
		i++;
	}
	return (len);
}

char		*procwstr(wchar_t *wstr)
{
	char	*outstr;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	if (wstr == 0)
		return (0);
	i = 0;
	len = ft_wstrlen(wstr);
	outstr = ft_strnew((size_t)len);
	while (wstr[i] != 0)
	{
		tmp = procwc(wstr[i]);
		j = 0;
		len = (int)ft_strlen(outstr);
		while (tmp[j] != 0)
		{
			outstr[len + j] = tmp[j];
			j++;
		}
		ft_memdel((void **)&tmp);
		i++;
	}
	return (outstr);
}
