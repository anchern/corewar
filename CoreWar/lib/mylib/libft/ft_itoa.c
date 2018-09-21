/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:49:43 by achernys          #+#    #+#             */
/*   Updated: 2017/11/10 17:49:58 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	res(char *str, long n)
{
	if ((n / 10) == 0)
	{
		*str = (char)(n % 10 + 48);
		return ;
	}
	res(str - 1, n / 10);
	*str = (char)(n % 10 + 48);
}

char		*ft_itoa(int n)
{
	size_t	size;
	int		tmp;
	char	*str;

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
		res(&str[size - 1], -(long)n);
		str[0] = '-';
	}
	else
		res(&str[size - 1], n);
	return (str);
}
