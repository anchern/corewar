/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 21:52:07 by achernys          #+#    #+#             */
/*   Updated: 2017/11/10 21:52:17 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(long n)
{
	if (n / 10 == 0)
	{
		ft_putchar((char)(n % 10 + 48));
		return ;
	}
	print(n / 10);
	ft_putchar((char)(n % 10 + 48));
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		print(-(long)n);
	}
	else
		print(n);
}
