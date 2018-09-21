/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:31:13 by achernys          #+#    #+#             */
/*   Updated: 2017/11/06 22:33:15 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	big = ft_strchr(big, little[0]);
	while (big != '\0')
	{
		i = 0;
		while (little[i] != '\0')
		{
			if (little[i] != big[i])
				break ;
			i++;
		}
		if (i == ft_strlen(little))
			return ((char *)big);
		big = ft_strchr(big + 1, little[0]);
	}
	return (0);
}
