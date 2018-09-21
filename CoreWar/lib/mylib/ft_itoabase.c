/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:23:30 by achernys          #+#    #+#             */
/*   Updated: 2018/05/08 16:08:35 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	getlenstr(__uint128_t number, int base)
{
	int len;

	len = 1;
	while (number >= (__uint128_t)base)
	{
		number /= base;
		len++;
	}
	return (len);
}

static void	getres(char *str, __uint128_t number, int base, char sym)
{
	__uint128_t		res;

	if (number < (__uint128_t)base)
	{
		*str = (char)(number > 9 ? number - 10 + sym : number + '0');
		return ;
	}
	getres(str - 1, number / base, base, sym);
	res = number % base;
	*str = (char)(res > 9 ? res - 10 + sym : res + '0');
}

char		*ft_itoabase(__uint128_t number, int base, char sym)
{
	int		len;
	char	*outstr;

	len = getlenstr(number, base);
	outstr = ft_strnew((size_t)len);
	getres(&outstr[len - 1], number, base, sym);
	return (outstr);
}
