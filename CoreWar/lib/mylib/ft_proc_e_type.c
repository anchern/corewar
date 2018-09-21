/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_e_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:31:49 by achernys          #+#    #+#             */
/*   Updated: 2018/05/12 21:28:53 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*addepart(char *num, int minus, int power, char identifier)
{
	char	*tmpstr;
	char	*outstr;
	size_t	lennum;

	lennum = ft_strlen(num);
	tmpstr = ft_strnew(lennum + (size_t)(power < 10 ? 3 : 2));
	ft_strcpy(tmpstr, num);
	tmpstr[lennum] = identifier;
	tmpstr[lennum + 1] = (char)(minus ? '-' : '+');
	if (power < 10)
		tmpstr[lennum + 2] = '0';
	outstr = ft_strjoin(tmpstr, ft_itoa(power));
	ft_memdel((void **)&tmpstr);
	ft_memdel((void **)&num);
	return (outstr);
}

static void	takeeformatnum(long double *num, int *power)
{
	int			flag;
	int			intpart;
	long double	tmpnum;

	*power = 0;
	flag = fabsl(*num) < 1.0 ? 0 : 1;
	while ((fabsl(*num) >= 9.999999999999 || fabsl(*num) < 1.0) && *num != 0.0)
	{
		*num = flag ? *num / 10.0 : *num * 10.0;
		*power += 1;
	}
	tmpnum = *num;
	intpart = (int)*num;
	tmpnum -= (long double)intpart;
	if (fabsl(tmpnum) >= 0.5)
		intpart = intpart < 0 ? intpart - 1 : intpart + 1;
	if (abs(intpart) == 10)
	{
		*num /= 10;
		*power += flag == 1 ? 1 : -1;
	}
}

char		*transformftoue(char identifier, t_data *data,
							t_argptrsave *structarg)
{
	long double num;
	char		*res;
	char		*outstr;
	int			power;
	int			minus;

	if (data->bl == 1)
		num = get_ldouble(&structarg->argptrcurr);
	else
		num = get_double(&structarg->argptrcurr);
	if (isnan(num) || isinf(num))
		data->zero = 0;
	if (isnan(num))
		return (ft_strdup(identifier == 'E' ? "NAN" : "nan"));
	if (isinf(num))
		return (ft_strdup(identifier == 'E' ? "INF" : "inf"));
	minus = 0;
	if (fabsl(num) < 1.0 && num != 0.0)
		minus = 1;
	takeeformatnum(&num, &power);
	res = ft_ftoa(num, data->prec, data->hashtag);
	res = addepart(res, minus, power, identifier);
	if ((outstr = numnotationint(res, data, identifier)) != (char *)-1)
		return (outstr);
	return (res);
}
