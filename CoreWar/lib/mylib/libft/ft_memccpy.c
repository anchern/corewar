/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:37:03 by achernys          #+#    #+#             */
/*   Updated: 2017/11/11 06:01:25 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)src;
	while (i < n)
	{
		((unsigned char *)dst)[i] = tmp[i];
		if (tmp[i] == (unsigned char)c)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (0);
}
