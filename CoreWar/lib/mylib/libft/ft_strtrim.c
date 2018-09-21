/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:30:17 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 16:30:34 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*outs;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
	}
	if (i == ft_strlen(s))
	{
		if ((outs = ft_strnew(0)))
			return (outs);
	}
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
	{
		j--;
	}
	outs = ft_strsub(s, (unsigned int)i, (j - i) + 1);
	if (outs == NULL)
		return (NULL);
	return (outs);
}
