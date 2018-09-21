/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:49:43 by achernys          #+#    #+#             */
/*   Updated: 2018/05/03 19:54:20 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	res(char *str, __int128 n)
{
	if ((n / 10) == 0)
	{
		*str = (char)(n % 10 + 48);
		return ;
	}
	res(str - 1, n / 10);
	*str = (char)(n % 10 + 48);
}

char		*ft_bitoa(__int128 n)
{
	size_t		size;
	__int128	tmp;
	char		*str;

	size = 1;
	tmp = n;
	while ((tmp = tmp / 10) != 0)
		size++;
	if (n < 0)
		size++;
	if (!(str = ft_strnew(size)))
		return (NULL);
	str[size] = '\0';
	if (n < 0)
	{
		res(&str[size - 1], -n);
		str[0] = '-';
	}
	else
		res(&str[size - 1], n);
	return (str);
}
