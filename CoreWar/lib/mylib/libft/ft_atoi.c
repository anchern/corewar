/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:04:59 by anonymous         #+#    #+#             */
/*   Updated: 2018/03/24 12:38:44 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_lend(char *str)
{
	int		len;
	int		i;

	i = 0;
	while (str[i] == '0')
		i++;
	len = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char				*skip0(char *s)
{
	int i;

	i = 0;
	while (s[i] == '0')
		i++;
	return (&s[i]);
}

static unsigned long	atoul(char *str, long multiplication)
{
	unsigned long res;

	if (!ft_isdigit(*str))
		return (0);
	res = atoul(str + 1, multiplication / 10) + (*str - 48) * multiplication;
	return (res);
}

static unsigned char	overflow_check(char *str)
{
	unsigned long tmp;
	unsigned long max;

	if (ft_lend(str) > 20)
		return (1);
	tmp = atoul(skip0(str), ft_pow(10, ft_lend(str) - 1));
	max = 9223372036854775807U;
	if (tmp > max)
		return (1);
	return (0);
}

int						ft_atoi(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (!ft_lend(&str[++i]))
			return (0);
	if (i != 0 && str[i - 1] == '-')
	{
		if (overflow_check(&str[i]) == 1)
			return (0);
		return (-(int)atoul(skip0(&str[i]), ft_pow(10, ft_lend(&str[i]) - 1)));
	}
	if (str[i - 1] == '+')
	{
		if (overflow_check(&str[i]) == 1)
			return (-1);
		return ((int)atoul(skip0(&str[i]), ft_pow(10, ft_lend(&str[i]) - 1)));
	}
	if (!ft_lend(&str[i]))
		return (0);
	if (overflow_check(&str[i]) == 1)
		return (-1);
	return ((int)atoul(skip0(&str[i]), ft_pow(10, ft_lend(&str[i]) - 1)));
}
