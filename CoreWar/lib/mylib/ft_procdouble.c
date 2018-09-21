/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procdouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:26:01 by achernys          #+#    #+#             */
/*   Updated: 2018/05/08 17:56:14 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define MAXNUM 38

static void		get_lennum(int *len, long double *num)
{
	*len = 0;
	while (*num >= 1.0)
	{
		*num /= 10;
		*len += 1;
	}
}

static char		*procbigf(t_data *data, long double num, char identifier)
{
	int			len;
	char		*ipart;
	char		*res;
	char		*outstr;

	get_lennum(&len, &num);
	if (len <= MAXNUM)
		return (0);
	ipart = ft_bitoa((__int128)(num * (long double)ft_pow(10, MAXNUM)));
	if (data->prec == 0)
		res = ft_memset((void *)ft_strnew((size_t)len), '0', (size_t)len);
	else
	{
		res = ft_strnew((size_t)len + (size_t)(data->prec == -1 ? 6 :
							data->prec) + 1);
		ft_memset((void *)res, '0', (size_t)len +
			(size_t)(data->prec == -1 ? 6 : data->prec) + 1);
		res[len] = '.';
	}
	ft_memcpy((void *)res, (void *)ipart, ft_strlen(ipart));
	ft_memdel((void **)&ipart);
	if ((outstr = numnotationint(res, data, identifier)) != (char *)-1)
		return (outstr);
	return (res);
}

char			*procf(char identifier, t_data *data, t_argptrsave *structarg)
{
	long double num;
	char		*res;
	char		*outstr;

	if (data->bl == 1)
		num = get_ldouble(&structarg->argptrcurr);
	else
		num = get_double(&structarg->argptrcurr);
	if (isnan(num) || isinf(num))
		data->zero = 0;
	if (isnan(num))
		return (ft_strdup(identifier == 'F' ? "NAN" : "nan"));
	if (isinf(num))
		return (ft_strdup(identifier == 'F' ? "INF" : "inf"));
	if ((outstr = procbigf(data, num, identifier)))
		return (outstr);
	res = ft_ftoa(num, data->prec, data->hashtag);
	if ((outstr = numnotationint(res, data, identifier)) != (char *)-1)
		return (outstr);
	return (res);
}
