/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:21:36 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 14:21:39 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*outs;

	if (s == NULL)
		return (NULL);
	i = 0;
	outs = ft_strnew(ft_strlen(s));
	if (outs == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		outs[i] = (*f)(i, s[i]);
		i++;
	}
	return (outs);
}
