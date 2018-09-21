/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:07:03 by achernys          #+#    #+#             */
/*   Updated: 2018/04/20 21:07:03 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_realloc(char **src, size_t size, size_t reqsize)
{
	char *str_tmp;

	if (src == 0 || reqsize == 0)
		return (0);
	if (size == 0)
	{
		ft_memdel((void **)src);
		if (!(*src = (char *)ft_memalloc(reqsize)))
			return (1);
		return (0);
	}
	if (!(str_tmp = (char *)ft_memalloc(size > reqsize ? reqsize : size)))
		return (1);
	ft_memmove((void *)str_tmp, (void *)*src, size > reqsize ? reqsize : size);
	ft_memdel((void **)src);
	if (!(*src = (char *)ft_memalloc(reqsize)))
	{
		ft_memdel((void **)&str_tmp);
		return (1);
	}
	ft_memmove((void *)*src, (void *)str_tmp, size > reqsize ? reqsize : size);
	ft_memdel((void *)&str_tmp);
	return (0);
}
