/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:46:21 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 15:46:34 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	subs = ft_strnew(len);
	if (subs == NULL)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}
