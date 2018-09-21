/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:12:32 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 17:12:45 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimc(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	*outs;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == c)
	{
		i++;
	}
	if (i == ft_strlen(s))
	{
		if ((outs = ft_strnew(0)))
			return (outs);
	}
	while (s[j] == c)
	{
		j--;
	}
	outs = ft_strsub(s, (unsigned int)i, (j - i) + 1);
	if (outs == NULL)
		return (NULL);
	return (outs);
}
