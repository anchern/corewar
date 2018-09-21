/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 00:43:33 by achernys          #+#    #+#             */
/*   Updated: 2017/11/11 00:44:04 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(long n, int fd)
{
	if (n / 10 == 0)
	{
		ft_putchar_fd((char)(n % 10 + 48), fd);
		return ;
	}
	print(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + 48), fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		print(-(long)n, fd);
	}
	else
		print(n, fd);
}
