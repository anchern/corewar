/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:13:22 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 14:13:33 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		outs[i] = (*f)(s[i]);
		i++;
	}
	return (outs);
}
