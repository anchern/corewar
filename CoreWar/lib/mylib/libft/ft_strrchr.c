/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:07:51 by achernys          #+#    #+#             */
/*   Updated: 2017/11/02 16:08:01 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, char c)
{
	unsigned char	flag;
	size_t			i;
	size_t			tmp;

	flag = 0;
	i = 0;
	if (c == '\0')
		return (&((char *)s)[ft_strlen(s)]);
	while (((char *)s)[i] != '\0')
	{
		if (((char *)s)[i] == c)
		{
			tmp = i;
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		return (&((char *)s)[tmp]);
	return (0);
}
