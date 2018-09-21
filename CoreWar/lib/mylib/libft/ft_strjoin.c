/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:00:44 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 16:01:29 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joins;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joins = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (joins == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		joins[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		joins[i + j] = s2[j];
		j++;
	}
	return (joins);
}
