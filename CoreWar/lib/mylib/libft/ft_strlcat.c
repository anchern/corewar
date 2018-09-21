/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:03:53 by achernys          #+#    #+#             */
/*   Updated: 2017/11/01 15:05:37 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t lendst;
	size_t i;

	lendst = ft_strlen(dst);
	if (size <= lendst)
		return (size + ft_strlen(src));
	i = 0;
	while (i < (size - lendst - 1) && src[i] != '\0')
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + ft_strlen(src));
}
