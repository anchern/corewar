/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:59:29 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 12:59:46 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*mem;
	size_t			i;

	if (!(mem = (unsigned char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		mem[i] = 0;
		i++;
	}
	return ((void *)mem);
}
