/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:55:49 by achernys          #+#    #+#             */
/*   Updated: 2017/10/27 20:13:36 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int i;

	if (!dst || !src)
		return (0);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	i = (int)n - 1;
	while (i >= 0)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i--;
	}
	return (dst);
}
